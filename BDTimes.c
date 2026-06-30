#include "BDTimes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "BDPartidas.h"


//Carrega os times do arquivos csv
BDTimes* carregar_times(const char *arquivo, BDPartida *bdp){
   BDTimes *bd = malloc(sizeof(BDTimes));

   FILE *ftime = fopen(arquivo, "r");

   if(ftime == NULL){
      printf("Erro ao abrir arquivo\n");
      free(bd);
      return NULL;
   }

   bd->num = 0;
   bd->first = NULL;
   bd->last = NULL;

   char linha[100];
   fgets(linha, sizeof(linha), ftime);

   while(fgets(linha, sizeof(linha), ftime)){

      Time *t = malloc(sizeof(Time));

      char *dado;

      dado = strtok(linha, ",");
      t->id = atoi(dado);

      dado = strtok(NULL, "\n");
      strcpy(t->nome, dado);

      // Inicializa estatísticas
      t->V = 0;
      t->E = 0;
      t->D = 0;
      t->GM = 0;
      t->GS = 0;
      t->S = 0;
      t->PG = 0;

      bd_insert(bd, t);
   }

   fclose(ftime);

   // Calcula todas as estatísticas
   recalcular_times(bd, bdp);

   return bd;
}

int tam_bd(BDTimes *bd){
   return bd->num;
}

int bd_vazio(BDTimes *bd){
   return tam_bd(bd) == 0;
}

void bd_insert(BDTimes *bd,Time *t){
   t->next = bd->first;
   t->prev = NULL;
   if(!bd_vazio(bd)){
      bd->first->prev = t;
   }
   else{
      bd->last = t;
   }
   bd->first = t;
   bd->num++;
}

//Faz uma consulta para procurar times utilizando busca com prefixos
void consultar_time(char *busca, BDTimes *bd){
   //var caso não seja encontrado um time
   int erro = 1;

   //Cabeçalho tabulado
   printf("\n%-3s %-15s %-3s %-3s %-3s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

   //busca times pelo seu nome sem distinção de maiúscula ou minúscula
   for(Time *t = bd->first; t!= NULL; t=t->next){
      //time encontrado
      if(strncasecmp(t->nome, busca, strlen(busca)) == 0){
         //impressão tabulada dos times encontrados e atualização da var de erro
         printf("%-3d %-15s %-3d %-3d %-3d %-5d %-5d %-5d %-5d\n", t->id, t->nome, t->V, t->E, t->D, t->GM, t->GS, t->S, t->PG);
         erro = 0;
      }
   }
   //time não encontrado
   if(erro == 1){
      printf("\n\nNENHUM TIME ENCONTRADO");
   }
}

//Print de tabela tabulada de cada time e suas pontuações
void consultar_class(BDTimes *bd){
   if(bd_vazio(bd)){
        printf("Nao ha times cadastrados.\n");
        return;
   }

   //vetor de ponteiros para os times
   Time *vet[10];

   int i = 0;
   for(Time *t = bd->first; t != NULL; t = t->next){
        vet[i++] = t;
   }

   //selection sort
   for(i = 0; i < bd->num - 1; i++){
      int maior = i;

      for(int j = i + 1; j < bd->num; j++){
         if(vet[j]->PG > vet[maior]->PG){
            maior = j;
         }
         else if(vet[j]->PG == vet[maior]->PG){
            if(vet[j]->V > vet[maior]->V){
               maior = j;
            }
            else if(vet[j]->V == vet[maior]->V){
               if(vet[j]->S > vet[maior]->S){
                  maior = j;
               }
            }
         }
      }

      Time *aux = vet[i];
      vet[i] = vet[maior];
      vet[maior] = aux;
   }

   // impressão
   printf("\n%-3s %-15s %-3s %-3s %-3s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
   for(i = 0; i < bd->num; i++){
      printf("%-3d %-15s %-3d %-3d %-3d %-5d %-5d %-5d %-5d\n", vet[i]->id,vet[i]->nome,vet[i]->V,vet[i]->E,vet[i]->D,vet[i]->GM,vet[i]->GS,vet[i]->S,vet[i]->PG);
   }

}

//busca um time por id e o retorna
char *buscar_time(BDTimes *bd, int id){
   for(Time *t = bd->first; t != NULL; t = t->next){
      if(t->id == id)
         return t->nome;
   }
   return NULL;
}

void free_bdtimes(BDTimes *bd){
   Time *t = bd->first;

   while(t != NULL){
      Time *prox = t->next;
      free(t);
      t = prox;
   }

   free(bd);
}

void recalcular_times(BDTimes *times, BDPartida *partidas){

   // Zera todos os times
   for(Time *t = times->first; t != NULL; t = t->next){
      t->V = 0;
      t->E = 0;
      t->D = 0;
      t->GM = 0;
      t->GS = 0;
      t->S = 0;
      t->PG = 0;
   }

   // Percorre todas as partidas
   for(Partida *p = partidas->first; p != NULL; p = p->next){
      for(Time *t = times->first; t != NULL; t = t->next){
         if(t->id == p->time1){
            if(p->GolsTime1 > p->GolsTime2)
               t->V++;
            else if(p->GolsTime1 < p->GolsTime2)
               t->D++;
            else
               t->E++;
            t->GM += p->GolsTime1;
            t->GS += p->GolsTime2;
         }
         else if(t->id == p->time2){
            if(p->GolsTime2 > p->GolsTime1)
               t->V++;
            else if(p->GolsTime2 < p->GolsTime1)
               t->D++;
            else
               t->E++;
            t->GM += p->GolsTime2;
            t->GS += p->GolsTime1;
         }
      }
   }
   // Calcula saldo e pontos
   for(Time *t = times->first; t != NULL; t = t->next){
      t->S = t->GM - t->GS;
      t->PG = 3*t->V + t->E;
   }
}