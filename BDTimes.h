#ifndef BDTIMES_H
#define BDTIMES_H
#include "BDPartidas.h"

typedef struct time{
    int id;
    char nome[20];

    int V;
    int E;
    int D;
    int GM;
    int GS;
    int S;
    int PG;
    struct time *next;
    struct time *prev;
} Time;

typedef struct bdtime{
    int num;
    Time *first;
    Time *last;
} BDTimes;

//Carrega os times do arquivos csv
BDTimes* carregar_times(const char *arquivo, BDPartida *bdp);

int tam_bd(BDTimes *bd);

int bd_vazio(BDTimes *bd);

void bd_insert(BDTimes *bd,Time *t);

//Faz uma consulta para procurar times utilizando busca com prefixos
void consultar_time(char *busca, BDTimes *bd);

//Print de tabela tabulada de cada time e suas pontuações
void consultar_class(BDTimes *bd);

//busca um time por id e o retorna
char *buscar_time(BDTimes *bd, int id);

void free_bdtimes(BDTimes *bd);

void recalcular_times(BDTimes *times, BDPartida *partidas);

#endif