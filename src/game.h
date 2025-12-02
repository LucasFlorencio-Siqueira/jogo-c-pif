#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Board board;
    Board shots;
    Fleet fleet;
    char nickname[32];
} Player;

typedef struct {
    Player p1, p2;
    int current_player;
    int game_over;
} Game;

Game* criarJogo(int rows, int cols, char* nome1, char* nome2);
void destruirJogo(Game* game);
void inicializarJogador(Player* p, char* nome, int rows, int cols);
void posicionarFrotaAuto(Player* p);
CellState processarTiro(Player* atirador, Player* defensor, int row, int col);
void alternarTurno(Game* game);

#endif
