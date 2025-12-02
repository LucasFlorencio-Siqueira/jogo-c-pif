#include "game.h"
#include "rnd.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void inicializarJogador(Jogador* j, char* nome, int tam) {
    strcpy(j->apelido, nome);
    j->meuTabuleiro = criarTabuleiro(tam, tam);
    j->mapaTiros = criarTabuleiro(tam, tam);
    j->frota = criarFrota();
    
    j->totalTiros = 0;
    j->capacidadeHistorico = 5;
    j->historicoTiros = (Coordenada*) malloc(j->capacidadeHistorico * sizeof(Coordenada));
}

void registrarTiro(Jogador* j, int l, int c) {
    if (j->totalTiros >= j->capacidadeHistorico) {
        j->capacidadeHistorico *= 2;
        j->historicoTiros = (Coordenada*) realloc(j->historicoTiros, j->capacidadeHistorico * sizeof(Coordenada));
    }
    j->historicoTiros[j->totalTiros].r = l;
    j->historicoTiros[j->totalTiros].c = c;
    j->totalTiros++;
}

Jogo* criarJogo(int tam, char* nome1, char* nome2) {
    Jogo* novoJogo = (Jogo*) malloc(sizeof(Jogo));
    novoJogo->tamanhoTabuleiro = tam;
    novoJogo->jogadorAtual = 1;
    novoJogo->fimDeJogo = 0;
    
    inicializarJogador(&novoJogo->j1, nome1, tam);
    inicializarJogador(&novoJogo->j2, nome2, tam);
    
    return novoJogo;
}

void destruirJogo(Jogo* jogo) {
    destruirTabuleiro(jogo->j1.meuTabuleiro);
    destruirTabuleiro(jogo->j1.mapaTiros);
    destruirTabuleiro(jogo->j2.meuTabuleiro);
    destruirTabuleiro(jogo->j2.mapaTiros);
    destruirFrota(&jogo->j1.frota);
    destruirFrota(&jogo->j2.frota);
    free(jogo->j1.historicoTiros);
    free(jogo->j2.historicoTiros);
    free(jogo);
}

int validarPosicao(Tabuleiro* t, int l, int c, int tamanho, int orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int linhaAtual = l;
        int colAtual = c;
        
        if (orientacao == HORIZONTAL) colAtual += i;
        else linhaAtual += i;

        if (!coordenadaValida(t, linhaAtual, colAtual)) return 0;
        
        Celula* cel = pegarCelula(t, linhaAtual, colAtual);
        if (cel->estado != AGUA) return 0;
    }
    return 1;
}

void preencherPosicao(Tabuleiro* t, int l, int c, int tamanho, int orientacao, int id) {
    for (int i = 0; i < tamanho; i++) {
        int linhaAtual = l;
        int colAtual = c;
        
        if (orientacao == HORIZONTAL) colAtual += i;
        else linhaAtual += i;

        Celula* cel = pegarCelula(t, linhaAtual, colAtual);
        cel->estado = NAVIO;
        cel->idNavio = id;
    }
}

void posicionarFrotaAuto(Jogador* j) {
    for (int i = 0; i < j->frota.quantidade; i++) {
        Navio* navio = &j->frota.listaNavios[i];
        int posicionado = 0;
        
        while (!posicionado) {
            int l = gerarNumero(0, j->meuTabuleiro->linhas - 1);
            int c = gerarNumero(0, j->meuTabuleiro->colunas - 1);
            int orientacao = gerarNumero(0, 1);
            
            if (validarPosicao(j->meuTabuleiro, l, c, navio->tamanho, orientacao)) {
                preencherPosicao(j->meuTabuleiro, l, c, navio->tamanho, orientacao, i);
                navio->posicionado = 1;
                posicionado = 1;
            }
        }
    }
}

EstadoCelula processarTiro(Jogador* atirador, Jogador* alvo, int l, int c) {
    Celula* celAlvo = pegarCelula(alvo->meuTabuleiro, l, c);
    Celula* celTiro = pegarCelula(atirador->mapaTiros, l, c);

    if (celTiro->estado != AGUA) {
        return celTiro->estado;
    }

    registrarTiro(atirador, l, c);

    if (celAlvo->estado == NAVIO) {
        celAlvo->estado = ACERTO;
        celTiro->estado = ACERTO;
        
        int id = celAlvo->idNavio;
        alvo->frota.listaNavios[id].acertos++;
        
        return ACERTO;
    } else {
        celAlvo->estado = ERRO;
        celTiro->estado = ERRO;
        return ERRO;
    }
}

void alternarTurno(Jogo* jogo) {
    if (jogo->jogadorAtual == 1) jogo->jogadorAtual = 2;
    else jogo->jogadorAtual = 1;
}
