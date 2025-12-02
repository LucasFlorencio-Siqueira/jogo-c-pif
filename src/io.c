#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int menuPrincipal() {
    int opcao;
    printf("\n BATALHA NAVAL \n");
    printf("1. Novo Jogo\n");
    printf("2. Configuracoes\n");
    printf("3. Sair\n");
    printf("Escolha: ");
    
  
    if (scanf("%d", &opcao) != 1) {
        while(getchar() != '\n'); 
        return 0;
    }
    return opcao;
}

void configurarJogo(int* tamanho, char* modo) {
    printf("Tamanho do tabuleiro (6-26): ");
    scanf("%d", tamanho);
    if (*tamanho < 6) *tamanho = 6;
    if (*tamanho > 26) *tamanho = 26;

    printf("Modo (M = Manual, A = Automatico): ");
    scanf(" %c", modo);
    *modo = toupper(*modo);
}

void pedirNomes(char* nome1, char* nome2) {
    printf("Nome Jogador 1: ");
    scanf("%s", nome1);
    printf("Nome Jogador 2: ");
    scanf("%s", nome2);
}

int pedirTiro(int* row, int* col, int maxDim) {
    char coord[10];
    printf("Coordenada (ex: A5): ");
    scanf("%s", coord);

    char letra = toupper(coord[0]);
    *col = letra - 'A';
    *row = atoi(&coord[1]) - 1;

    if (*row >= 0 && *row < maxDim && *col >= 0 && *col < maxDim) {
        return 1;
    }
    return 0;
}

void mostrarTabuleiro(Board* board, int showShips) {
    printf("   ");
    for (int c = 0; c < board->cols; c++) {
        printf("%c ", 'A' + c);
    }
    printf("\n");

    for (int r = 0; r < board->rows; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < board->cols; c++) {
            Cell* cell = pegarCelula(board, r, c);
            char simbolo = '~';

            if (cell->state == CELL_WATER) simbolo = '~';
            else if (cell->state == CELL_MISS) simbolo = '.';
            else if (cell->state == CELL_HIT) simbolo = 'X';
            else if (cell->state == CELL_SHIP) {
                if (showShips) simbolo = 'S';
                else simbolo = '~';
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

void mostrarTelaJogo(Player* atual, Player* inimigo) {
    printf("\n--- Turno de %s ---\n", atual->nickname);
    printf("\nMAPA DE TIROS (Inimigo):\n");
    mostrarTabuleiro(&atual->shots, 0);
    
    printf("\nSEU TABULEIRO:\n");
    mostrarTabuleiro(&atual->board, 1);
}

void mostrarMensagemTiro(CellState resultado, char* nomeNavio) {
    if (resultado == CELL_MISS) {
        printf("Resultado: AGUA!\n");
    } else if (resultado == CELL_HIT) {
        printf("Resultado: ACERTOU!\n");
        if (nomeNavio != NULL) {
            printf("Voce acertou um %s!\n", nomeNavio);
        }
    } else {
        printf("Resultado: Tiro repetido ou invalido.\n");
    }
    printf("Pressione ENTER...");
    getchar(); 
    getchar();
}

void mostrarVencedor(Player* vencedor) {
    printf("\n*** FIM DE JOGO ***\n");
    printf("O vencedor foi: %s\n", vencedor->nickname);
}
