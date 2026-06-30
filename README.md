# TP-Parte-2-Campeonato-Computacional-de-Futebol-Nelson

Este projeto é um sistema simples de gerenciamento de campeonato de futebol. O sistema faz a busca de times e partidas por prefixos, adiciona, remove ou atualiza partidas, e apresenta uma tabela de classificação por meio de dados inicialmente lidos em arquivos CSV.
## Sobre os arquivos
| Arquivo  | Descrição |
| ------------- | ------------- |
| `main.c`  | Função main e auxiliares de menu |
| `BDTimes.c` | Implementação das funcionalidades relacionadas com o TAD Time e BDTimes |
| `BDTimes.h` | Definições das estruturas de times e declarações das funções de times |
| `BDPartidas.c` | Implementação das funcionalidades relacionadas com o TAD Partida e BDPartida |
| `BDPartidas.h` | Definições das estruturas de partidas e declarações das funções de partidas |
| `Makefile` | Script para compilação automatica |
| `times.csv` | Base de dados do time para leitura de dados |
| `partidas_vazio.csv` | Base de dados de partidas, apenas com o cabeçalho |
| `partidas_parcial.csv` | Base de dados de partidas, com 45 entradas de dados |
| `partidas_completo.csv` | Base de dados de partidas, com 90 entradas de dados |

## TADs Utilizados
1. **Time**
O TAD Time representa um nó individual da lista encadeada de times, com os seguintes campos:
+ `id (int)`: Número de identificação do time.
+ `nome[20] (char)`: Nome do time.
+ `V (int)`: Quantas vitorias o time tem.
+ `E (int)`: Quantos empates o time tem.
+ `D (int)`: Quantas derrotas o time tem.
+ `GM (int)`: Quantos gols o time marcou.
+ `GS (int)`: Quantos gols o time sofreu.
+ `S (int)`: Numero do saldo de gols.
+ `PG (int)`: Pontos ganhos no campeonato (3v+E).
+ `next (struct time)`: Proximo node da lista encadeada.
+ `prev (struct time)`: Node anterior na lista encadeada.

2. **BDTimes**
O TAD BDTimes representa a lista encadeada dos times, com os seguintes campos:
+ `first (struct time)`: Ultimo time adicionado à lista encadeada.
+ `last (struct time)`: Ultimo time adicionado à lista encadeada.
+ `num (int)`: Número de nós na lista encadeada.

3. **Partida**
O TAD Partida representa um nó da lista encadeada de partidas, com os seguintes campos:
+ `id (int)`: Número de identificação da partida.
+ `time1 (int)`: ID do time mandante.
+ `time2 (int)`: ID do time visitante.
+ `GolsTime1 (int)`: Gols do time mandante.
+ `GolsTime2 (int)`: Gols do time visitante.

4. **BDPartida**
O TAD BDPartida representa a lista encadeada de partidas, tem os seguintes campos:
+ `first (struct time)`: Ultima partida adicionado à lista encadeada.
+ `last (struct time)`: Ultima partida adicionado à lista encadeada.
+ `num (int)`: Número de nós na lista encadeada.

## Funcionalidades Implementadas e Decisões de Implementação

+ Leitura e carregamento do CSV: Leitura e armazenamento dos dados do arquivo partidas.csv selecionado na linha 25 do `main.c` no vetor dinámico BDPartida seguido da leitura e armazenamento do times.csv em conjunto dos dados armazenados da leitura do partidas.csv para os dados ausentes em time.csv.
+ Busca por prefixo: Busca por times ou partidas utilizando o prefixo de um time por meio do `strncasecmp()`.
+ Impressão tabulada: Tabulação dos resultados da busca ou classificação por meio da formatação do `printf()`.
+ Ordenação: Ordenação de times para impressão da classificação por meio de algoritmo de selection sort.
+ Manipulação de lista encadeada: Inserção, remoção ou atualização de partidas por meio de respectivas funções.
+ Funções de auxilio de Menu: Funções para resetar o terminal e função para pausar o menu antes de resetar o terminal para possibilitar que o usuário veja o resultado de sua ação.
+ Modularização do codigo: Funções especificas para a busca, leitura e armazenamento de dados de arquivos ,manipulação de dados, e impressão de dados.

## Como executar
1. **Requisitos**
   - Compilador de c
   - make
   - Arquivos de leitura
2. Escolhar o arquivo partidas.csv(vazio,parcial,completo) na linha 25 do main (**Opcional, caso não mude o arquivo selecionado o default sera o completo**)
3. No terminal, dentro do diretório do projeto
   - Compila e executa
   ```
   make
   ```
   - Limpeza dos arquivos objeto
   ```
   make clean
   ```  
   
