#ifndef BOARD_H
#define BOARD_H

typedef enum {
    AGUA,
    NAVIO,
    ACERTO,
    ERRO
} EstadoCelula;

typedef struct {
    EstadoCelula estado;
    int idNavio;
} Celula;

typedef struct {
    int linhas;
    int colunas;
    Celula *celulas;
} Tabuleiro;

Tabuleiro* criarTabuleiro(int linhas, int colunas);
void destruirTabuleiro(Tabuleiro* tabuleiro);
void limparTabuleiro(Tabuleiro* tabuleiro);
Celula* pegarCelula(Tabuleiro* tabuleiro, int linha, int coluna);
int coordenadaValida(Tabuleiro* tabuleiro, int linha, int coluna);

#endif
