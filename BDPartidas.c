#include "BDPartidas.h"
#include "BDTimes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

BDPartida* carregar_partidas(const char* arquivo){
    BDPartida *bd = malloc(sizeof(BDPartida));
    bd->first = NULL;
    bd->last = NULL;
    bd->num = 0;

    FILE *fpart = fopen(arquivo,"r");

    //Verifica se arquivo abriu
    if(fpart == NULL){
      printf("Erro ao abrir arquivo\n");
      free(bd);
      return NULL;
    }

    char linha[100];
    fgets(linha,sizeof(linha),fpart);//pula cabeçario

    while(fgets(linha,sizeof(linha),fpart)){
        Partida *p = malloc(sizeof(Partida));
        char *dado;

        //carrega ID
        dado = strtok(linha,",");
        p->id = atoi(dado);

        //time1
        dado = strtok(NULL, ",");
        p->time1 = atoi(dado);

        //time2
        dado = strtok(NULL, ",");
        p->time2 = atoi(dado);

        //golstime1
        dado = strtok(NULL, ",");
        p->GolsTime1 = atoi(dado);

        //golstime2
        dado = strtok(NULL, ",");
        p->GolsTime2 = atoi(dado);

        bdp_load_insert(bd,p); //adiciona partida ao vetor dinámico
    }

    fclose(fpart);
    return bd;
}

int tam_bdp(BDPartida *bd){
    return bd->num;
}

int bdp_vazio(BDPartida *bd){
    return tam_bdp(bd) == 0;
}

Partida *find_partida(int pos, BDPartida *bd){
    if(pos < 0 || pos >= bd->num){
    return NULL;
    }

    if(pos == 0){
        return bd->first;
    }
    Partida *p = bd->first;
    for(int i =1;i<pos+1;i++){
        p = p->next;
    }
    return p;
}

void bdp_load_insert(BDPartida *bd,Partida *p){
    p->next = bd->first;
    p->prev = NULL;
    if(!bdp_vazio(bd)){
        bd->first->prev = p;
    }
    else{
        bd->last = p;
    }
    bd->first = p;
    bd->num++;
}

void consultar_partidas(BDPartida *bdp, char c, char *busca, BDTimes *t){
    int erro = 1;   //var caso não encontre partidas
    switch(c){
        //busca por mandante
        case '1':
            printf("\n%-3s %-22s %-15s\n", "ID", "Time1", "Time2");
            for(Partida *p = bdp->first;p != NULL; p = p->next){
                if(strncasecmp(buscar_time(t, p->time1), busca, strlen(busca)) == 0){
                    printf("%-3d %-15s %d x %-2d %-15s\n", p->id, buscar_time(t, p->time1), p->GolsTime1, p->GolsTime2, buscar_time(t, p->time2));
                    erro = 0;
                }
            }
            if(erro == 1){
                printf("\n\nNENHUMA PARTIDA ENCONTRADA");
            }
            break;
        //busca por visitante
        case '2':
            printf("\n%-3s %-22s %-15s\n", "ID", "Time1", "Time2");
            for(Partida *p = bdp->first;p != NULL; p = p->next){
                if(strncasecmp(buscar_time(t, p->time2), busca, strlen(busca)) == 0){
                    printf("%-3d %-15s %d x %-2d %-15s\n", p->id, buscar_time(t, p->time1), p->GolsTime1, p->GolsTime2, buscar_time(t, p->time2));
                    erro = 0;
                }
            }
            if(erro == 1){
                printf("\n\nNENHUMA PARTIDA ENCONTRADA");
            }
            break;
        //busca por ambos
        case '3':
            printf("\n%-3s %-22s %-15s\n", "ID", "Time1", "Time2");
            for(Partida *p = bdp->first;p != NULL; p = p->next){
                if(strncasecmp(buscar_time(t, p->time1), busca, strlen(busca)) == 0 || strncasecmp(buscar_time(t, p->time2), busca, strlen(busca)) == 0){
                    printf("%-3d %-15s %d x %-2d %-15s\n", p->id, buscar_time(t, p->time1), p->GolsTime1, p->GolsTime2, buscar_time(t, p->time2));
                    erro = 0;
                }
            }
            if(erro == 1){
                printf("\n\nNENHUMA PARTIDA ENCONTRADA");
            }
            break;
    }
}

void free_bdpartidas(BDPartida *bd){
    Partida *p = bd->first;

    while(p != NULL){
        Partida *prox = p->next;
        free(p);
        p = prox;
    }

    free(bd);
}

void update_partida(BDPartida *partidas, int busca, BDTimes *times){
    char novo1, novo2, conf = ' ';
    Partida *p = partidas->first;

    while(p != NULL && p->id != busca){
        p = p->next;
    }

    if(p == NULL){
        printf("Partida nao encontrada.\n");
        return;
    }
    int velho1 = p->GolsTime1;
    int velho2 = p->GolsTime2;

    printf("\nDigite os novos gols do Time1 e do Time2 respectivamente (use '-' para manter o valor atual):\n");

    scanf(" %c", &novo1);
    scanf(" %c", &novo2);

    while((novo1 != '-' && (novo1 < '0' || novo1 > '9')) ||
          (novo2 != '-' && (novo2 < '0' || novo2 > '9'))){

        printf("Valores invalidos. Digite novamente:\n");

        scanf(" %c", &novo1);
        scanf(" %c", &novo2);
    }

    if(novo1 != '-'){
        p->GolsTime1 = novo1 - '0';
    }
    if(novo2 != '-'){
        p->GolsTime2 = novo2 - '0';
    }
    printf("\nOs valores abaixo estao corretos?(Y/N)\n");
    printf("%-3d %-15s %d x %-2d %-15s\n\n", p->id, buscar_time(times, p->time1), p->GolsTime1, p->GolsTime2, buscar_time(times, p->time2));
    while(conf!='Y' && conf!='y' && conf!='N' && conf!='n'){
        scanf(" %c", &conf);
        switch(conf){
            case 'Y':
            case 'y':
                recalcular_times(times, partidas);
                break;
            case 'N':
            case 'n':
                p->GolsTime1 = velho1;
                p->GolsTime2 = velho2;
                printf("\nVoltando ao menu principal\n");
                return;
            default:
                printf("\nOpçao invalida, escolha novamente (Y/N)\n");
                break;
            }
    }
    printf("\nPartida atualizada com sucesso!\n");
}

void remove_partida(BDPartida *bd, int id, BDTimes *times){
    char conf = ' ';
    for(Partida *p = bd->first;p != NULL;p=p->next){
        if(p->id == id){
            printf("Tem certeza que deseja remover a partida abaixo? (Y/N)\n");
            printf("%-3d %-15s %d x %-2d %-15s\n\n", p->id, buscar_time(times, p->time1), p->GolsTime1, p->GolsTime2, buscar_time(times, p->time2));
            while(conf!='Y' && conf!='y' && conf!='N' && conf!='n'){
                scanf(" %c", &conf);
                switch(conf){
                    case 'Y':
                    case 'y':
                    printf("\nRemocao com sucesso.\n");
                        if(bd->first == bd->last){
                            bd->first = NULL;
                            bd->last = NULL;
                            free(p);
                            bd->num--;
                            return;
                        }
                        else if(p == bd->first){
                            bd->first = p->next;
                            bd->first->prev = NULL;
                            free(p);
                            bd->num--;
                            return;
                        }
                        else if(p == bd->last){
                            bd->last = bd->last->prev;
                            bd->last->next = NULL;
                            free(p);
                            bd->num--;
                            return;
                        }
                        else{
                            p->prev->next = p->next;
                            p->next->prev = p->prev;
                            free(p);
                            bd->num--;
                            return;
                        }
                    case 'N':
                    case 'n':
                        printf("\nVoltando ao menu principal\n");
                        return;
                    default:
                        printf("\nOpcao invalida\n");
                        break;
                }
            }
        }
    }
    printf("Partida não encontrada\n");
}

void inserir_partida(BDPartida *bd, BDTimes *times,int newID){
    Partida *p = malloc(sizeof(Partida));
    char conf = ' ';

    p->id = newID;
    p->time1 = 0;
    p->time2 = 0;
    p->GolsTime1 = -1;
    p->GolsTime2 = -1;

    printf("Para inserir uma nova partida por favor preencha os dados na ordem de Time1, Time2, GolsTime1, GolsTime2:\n");
    while(p->time1 == p->time2){
        printf("Time 1: ");
        scanf("%d",&p->time1);
        printf("Time 2: ");
        scanf("%d",&p->time2);
    }
    while(p->GolsTime1<0 || p->GolsTime2<0){
        printf("Gols Time 1: ");
        scanf("%d",&p->GolsTime1);
        printf("Gols Time 2: ");
        scanf("%d",&p->GolsTime2);
    }    
    printf("\nConfirmar a inserção para esta partida? (Y/N):\n");
    printf("%-3d %-15s %d x %-2d %-15s\n\n", p->id, buscar_time(times, p->time1), p->GolsTime1, p->GolsTime2, buscar_time(times, p->time2));
    while(conf!='Y' && conf!='y' && conf!='N' && conf!='n'){
        scanf(" %c", &conf);
        switch(conf){
            case 'Y':
            case 'y':
                p->next = bd->first;
                p->prev = NULL;
                if(bd->first != NULL){
                    bd->first->prev = p;
                }
                else{
                    bd->last = p;
                }
                bd->first = p;
                bd->num++;
                printf("\nInsercao bem sucedida\n");
                return;
            case 'N':
            case 'n':
                free(p);
                printf("\nVoltando ao menu principal\n");
                return;
            default:
                printf("\nOpcao invalida\n");
                break;
        }
    }   
}