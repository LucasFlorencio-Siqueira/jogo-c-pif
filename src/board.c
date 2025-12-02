#include "board.h"
#include <stdlib.h>
#include <stdio.h>

void inicializarTabuleiro(Board* board, int rows, int cols) {
    board->rows = rows;
    board->cols = cols;
    board->cells = (Cell*) malloc(rows * cols * sizeof(Cell));
    limparTabuleiro(board);
}

void liberarTabuleiro(Board* board) {
    if (board->cells != NULL) {
        free(board->cells);
    }
}

void limparTabuleiro(Board* board) {
    int total = board->rows * board->cols;
    for (int i = 0; i < total; i++) {
        board->cells[i].state = CELL_WATER;
        board->cells[i].ship_id = -1;
    }
}

Cell* pegarCelula(Board* board, int row, int col) {
    if (!coordenadaValida(board, row, col)) {
        return NULL;
    }
    int index = (row * board->cols) + col;
    return &board->cells[index];
}

int coordenadaValida(Board* board, int row, int col) {
    return (row >= 0 && row < board->rows && col >= 0 && col < board->cols);
}
