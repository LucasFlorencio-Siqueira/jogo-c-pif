#include "board.h"
#include <stdlib.h>
#include <stdio.h>

Tabuleiro* criarTabuleiro(int linhas, int colunas) {
    Tabuleiro* t = (Tabuleiro*) malloc(sizeof(Tabuleiro));
    t->linhas = linhas;
    t->colunas = colunas;
    t->celulas = (Celula*) malloc(linhas * colunas * sizeof(Celula));
    limparTabuleiro(t);
    return t;
}

void destruirTabuleiro(Tabuleiro* tabuleiro) {
    if (tabuleiro != NULL) {
        free(tabuleiro->celulas);
        free(tabuleiro);
    }
}

void limparTabuleiro(Tabuleiro* tabuleiro) {
    int total = tabuleiro->linhas * tabuleiro->colunas;
    for (int i = 0; i < total; i++) {
        tabuleiro->celulas[i].estado = AGUA;
        tabuleiro->celulas[i].idNavio = -1;
    }
}

Celula* pegarCelula(Tabuleiro* tabuleiro, int linha, int coluna) {
    if (!coordenadaValida(tabuleiro, linha, coluna)) {
        return NULL;
    }
    int indice = (linha * tabuleiro->colunas) + coluna;
    return &tabuleiro->celulas[indice];
}

int coordenadaValida(Tabuleiro* tabuleiro, int linha, int coluna) {
    if (linha >= 0 && linha < tabuleiro->linhas && coluna >= 0 && coluna < tabuleiro->colunas) {
        return 1;
    }
    return 0;
}
