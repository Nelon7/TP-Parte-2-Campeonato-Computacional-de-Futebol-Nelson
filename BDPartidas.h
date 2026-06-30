#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H


typedef struct partida{
    int id;
    int time1;
    int time2;
    int GolsTime1;
    int GolsTime2;
    struct partida *next;
    struct partida *prev;
} Partida;

typedef struct bdpartida{
    int num;
    Partida *first;
    Partida *last;
} BDPartida;

typedef struct bdtime BDTimes;


//carrega as partidas do BD
BDPartida* carregar_partidas(const char* arquivo);

//Tamanho do BD
int tam_bdp(BDPartida *bd);

//BD vazio?
int bdp_vazio(BDPartida *bd);

//inserção do vetor dinámico
void bdp_load_insert(BDPartida *bd,Partida *p);

//busca por prefixo de partidas
void consultar_partidas(BDPartida *bdp, char c, char *busca, BDTimes *t);

Partida *find_partida(int pos, BDPartida *bd);

void free_bdpartidas(BDPartida *bd);

void update_partida(BDPartida *partidas, int busca, BDTimes *times);

void remove_partida(BDPartida *bd, int id, BDTimes *times);

void inserir_partida(BDPartida *bd, BDTimes *times,int newID);

#endif
