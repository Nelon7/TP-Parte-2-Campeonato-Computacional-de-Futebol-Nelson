#include "BDTimes.h"
#include "BDPartidas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Limpa o terminal
void limpar_tela(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Pausa para ver o resultado antes de limpar o terminal
void pausa(){
  printf("\n\nAperte ENTER para prosseguir");
  getchar();
  getchar();
}

int main(){
  BDPartida *partidas = carregar_partidas("partidas_parcial.csv"); //carega as partidas do BD
  if(partidas == NULL){
    return 1; //Termina o codigo em caso de erro ao carregar partidas
  }

  BDTimes *times = carregar_times("times.csv", partidas); // carrega os times do BD
  if(times == NULL){
    return 1; //Termina o codigo em caso de erro ao carregar times
  }
  
  //variaveis de menu/busca
  char menuP = ' '; //menu principal
  char menuS = ' '; //menu secundário
  char busca[15]; // utilizada para buscas de time/partidas
  int buscaID;

  while(menuP != 'q' && menuP != 'Q'){
    //Menu principal
    printf("1- Consultar time\n2- Consultar partida\n3- Atualizar partida\n4- Remover partida\n5- Inserir partida\n6- Imprimir tabela de Classificacao\nQ- Sair\n\n");
    scanf(" %c", &menuP);

    limpar_tela();

    switch(menuP){
      //Consulta de times
      case '1':
        printf("Digite o nome ou prefixo do time:\n\n");
        scanf(" %14s", busca);
        consultar_time(busca, times);

        pausa();
        limpar_tela();

        break;
      //Consulta de Partidas
      case '2':
        printf("Escolha o modo de consulta\n");
        printf("1 - Por time mandante\n2 - Por time visitante\n3 - Por time mandante ou visitante\n4 - Voltar ao menu principal\n\n");
        scanf(" %c", &menuS);

        //opção invalida
        while(menuS != '1' && menuS != '2' && menuS != '3' && menuS != '4'){
          limpar_tela();

          printf("Opcao invalida, escolha novamente\n");

          printf("1 - Por time mandante\n2 - Por time visitante\n3 - Por time mandante ou visitante\n4 - Voltar ao menu principal\n\n");
          scanf(" %c", &menuS);
        }
        //opção valida porem que não volta para o menu principal
        if(menuS != '4'){
          printf("Digite o nome:\n");
          scanf(" %14s", busca);
      
          consultar_partidas(partidas, menuS, busca, times);
        }

        pausa();
        limpar_tela();

        break;
      //Atualizar Partida
      case '3':
        printf("Digite o ID da partida que deseja atualizar\n");

        scanf("%d", &buscaID);

        update_partida(partidas,buscaID, times);

        pausa();
        limpar_tela();

        break;
      //Remover Partida
      case '4':
        printf("Digite o ID da partida a ser removida\n");
        scanf("%d", &buscaID);

        remove_partida(partidas, buscaID, times);
        recalcular_times(times,partidas);

        pausa();
        limpar_tela();

        break;
      //Inserir partida
      case '5':
        inserir_partida(partidas,times,partidas->first->id+1);
        recalcular_times(times,partidas);

        pausa();
        limpar_tela();

        break;
      //Consulta de classificação
      case '6':
        consultar_class(times);

        pausa();
        limpar_tela();

        break;
      //Saída
      case 'q':
      case 'Q':
        printf("Tchau!");
        break;
      //Opção inválida
      default:
        printf("Opcao invalida, selecione novamente.");

        pausa();
        limpar_tela();
        break;
    }
  }

  free_bdtimes(times);
  free_bdpartidas(partidas);
  return 0;
}