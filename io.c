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
    printf("\n=== BATALHA NAVAL ===\n");
    printf("1. Novo Jogo\n");
    printf("2. Configuracoes\n");
    printf("3. Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
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

int pedirTiro(int* linha, int* coluna, int tamanhoTabuleiro) {
    char coord[10];
    printf("Coordenada (ex: A5): ");
    scanf("%s", coord);

    char letra = toupper(coord[0]);
    *coluna = letra - 'A';
    *linha = atoi(&coord[1]) - 1;

    if (*linha >= 0 && *linha < tamanhoTabuleiro && *coluna >= 0 && *coluna < tamanhoTabuleiro) {
        return 1;
    }
    return 0;
}

void mostrarTabuleiro(Tabuleiro* t, int esconderNavios) {
    printf("   ");
    for (int c = 0; c < t->colunas; c++) {
        printf("%c ", 'A' + c);
    }
    printf("\n");

    for (int r = 0; r < t->linhas; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < t->colunas; c++) {
            Celula* cel = pegarCelula(t, r, c);
            char simbolo = '~';

            if (cel->estado == AGUA) simbolo = '~';
            else if (cel->estado == ERRO) simbolo = 'o';
            else if (cel->estado == ACERTO) simbolo = 'X';
            else if (cel->estado == NAVIO) {
                if (esconderNavios) simbolo = '~';
                else simbolo = 'S';
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

void mostrarTelaJogo(Jogador* jogadorAtual, Jogador* oponente) {
    printf("\n--- Turno de %s ---\n", jogadorAtual->apelido);
    printf("\nMAPA DE TIROS (Inimigo):\n");
    mostrarTabuleiro(jogadorAtual->mapaTiros, 1);
    
    printf("\nSEU TABULEIRO:\n");
    mostrarTabuleiro(jogadorAtual->meuTabuleiro, 0);
}

void mostrarMensagemTiro(EstadoCelula resultado, char* nomeNavio) {
    if (resultado == ERRO) {
        printf("Resultado: AGUA!\n");
    } else if (resultado == ACERTO) {
        printf("Resultado: ACERTOU!\n");
        if (nomeNavio != NULL) {
            printf("Voce acertou um %s!\n", nomeNavio);
        }
    }
    printf("Pressione ENTER...");
    getchar(); 
    getchar();
}

void mostrarVencedor(Jogador* vencedor) {
    printf("\n*** FIM DE JOGO ***\n");
    printf("O vencedor foi: %s\n", vencedor->apelido);
    printf("Total de tiros disparados: %d\n", vencedor->totalTiros);
}
