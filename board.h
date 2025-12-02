#ifndef BOARD_H
#define BOARD_H

typedef enum { CELL_WATER, CELL_SHIP, CELL_HIT, CELL_MISS } CellState;

typedef struct {
    CellState state;
    int ship_id;
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells;
} Board;

void inicializarTabuleiro(Board* board, int rows, int cols);
void liberarTabuleiro(Board* board);
void limparTabuleiro(Board* board);
Cell* pegarCelula(Board* board, int row, int col);
int coordenadaValida(Board* board, int row, int col);

#endif
