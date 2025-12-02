#ifndef IO_H
#define IO_H

#include "game.h"

int menuPrincipal();
void configurarJogo(int* tamanho, char* modo);
void pedirNomes(char* nome1, char* nome2);
int pedirTiro(int* linha, int* coluna, int tamanhoTabuleiro);
void mostrarTelaJogo(Jogador* jogadorAtual, Jogador* oponente);
void mostrarMensagemTiro(EstadoCelula resultado, char* nomeNavio);
void mostrarVencedor(Jogador* vencedor);
void limparTela();
void mostrarTabuleiro(Tabuleiro* t, int esconderNavios);

#endif
