#ifndef IO_H
#define IO_H

#include "game.h"

int menuPrincipal();
void configurarJogo(int* tamanho, char* modo);
void pedirNomes(char* nome1, char* nome2);
int pedirTiro(int* row, int* col, int maxDim);
void mostrarTelaJogo(Player* atual, Player* inimigo);
void mostrarMensagemTiro(CellState resultado, char* nomeNavio);
void mostrarVencedor(Player* vencedor);
void limparTela();
void mostrarTabuleiro(Board* board, int showShips);

#endif
