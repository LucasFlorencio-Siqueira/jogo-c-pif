#include "game.h"
#include "rnd.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void inicializarJogador(Player* p, char* nome, int rows, int cols) {
    strcpy(p->nickname, nome);
    inicializarTabuleiro(&p->board, rows, cols);
    inicializarTabuleiro(&p->shots, rows, cols);
    inicializarFrota(&p->fleet);
}

Game* criarJogo(int rows, int cols, char* nome1, char* nome2) {
    Game* jogo = (Game*) malloc(sizeof(Game));
    jogo->current_player = 1;
    jogo->game_over = 0;

    inicializarJogador(&jogo->p1, nome1, rows, cols);
    inicializarJogador(&jogo->p2, nome2, rows, cols);

    return jogo;
}

void destruirJogo(Game* game) {
    liberarTabuleiro(&game->p1.board);
    liberarTabuleiro(&game->p1.shots);
    liberarFrota(&game->p1.fleet);

    liberarTabuleiro(&game->p2.board);
    liberarTabuleiro(&game->p2.shots);
    liberarFrota(&game->p2.fleet);

    free(game);
}

int validarPosicao(Board* board, int row, int col, int len, Orientation orient) {
    for (int i = 0; i < len; i++) {
        int r = row;
        int c = col;

        if (orient == ORIENT_H) c += i;
        else r += i;

        if (!coordenadaValida(board, r, c)) return 0;
        
        Cell* cell = pegarCelula(board, r, c);
        if (cell->state != CELL_WATER) return 0;
    }
    return 1;
}

void preencherPosicao(Board* board, int row, int col, int len, Orientation orient, int shipId) {
    for (int i = 0; i < len; i++) {
        int r = row;
        int c = col;

        if (orient == ORIENT_H) c += i;
        else r += i;

        Cell* cell = pegarCelula(board, r, c);
        cell->state = CELL_SHIP;
        cell->ship_id = shipId;
    }
}

void posicionarFrotaAuto(Player* p) {
    for (int i = 0; i < p->fleet.count; i++) {
        Ship* s = &p->fleet.ships[i];
        int placed = 0;

        while (!placed) {
            int r = gerarNumero(0, p->board.rows - 1);
            int c = gerarNumero(0, p->board.cols - 1);
            Orientation o = (gerarNumero(0, 1) == 0) ? ORIENT_H : ORIENT_V;

            if (validarPosicao(&p->board, r, c, s->length, o)) {
                preencherPosicao(&p->board, r, c, s->length, o, i);
                s->placed = 1;
                placed = 1;
            }
        }
    }
}

CellState processarTiro(Player* atirador, Player* defensor, int row, int col) {
    Cell* alvo = pegarCelula(&defensor->board, row, col);
    Cell* tiro = pegarCelula(&atirador->shots, row, col);

    if (tiro->state != CELL_WATER) {
        return tiro->state;
    }

    if (alvo->state == CELL_SHIP) {
        alvo->state = CELL_HIT;
        tiro->state = CELL_HIT;

        int id = alvo->ship_id;
        defensor->fleet.ships[id].hits++;
        return CELL_HIT;
    } else {
        alvo->state = CELL_MISS;
        tiro->state = CELL_MISS;
        return CELL_MISS;
    }
}

void alternarTurno(Game* game) {
    game->current_player = (game->current_player == 1) ? 2 : 1;
}
