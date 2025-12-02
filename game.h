#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    int r, c;
} Coordenada;

typedef struct {
    char apelido[30];
    Tabuleiro* meuTabuleiro;
    Tabuleiro* mapaTiros;
    Frota frota;
    
    Coordenada* historicoTiros;
    int totalTiros;
    int capacidadeHistorico;
} Jogador;

typedef struct {
    Jogador j1;
    Jogador j2;
    int jogadorAtual;
    int tamanhoTabuleiro;
    int fimDeJogo;
} Jogo;

Jogo* criarJogo(int tam, char* nome1, char* nome2);
void destruirJogo(Jogo* jogo);
void inicializarJogador(Jogador* j, char* nome, int tam);
void posicionarFrotaAuto(Jogador* j);
EstadoCelula processarTiro(Jogador* atirador, Jogador* alvo, int l, int c);
void registrarTiro(Jogador* j, int l, int c);
void alternarTurno(Jogo* jogo);

#endif
