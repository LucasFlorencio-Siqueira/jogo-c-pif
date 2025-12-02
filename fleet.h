#ifndef FLEET_H
#define FLEET_H

typedef enum {
    HORIZONTAL,
    VERTICAL
} Orientacao;

typedef struct {
    char nome[20];
    int tamanho;
    int acertos;
    int posicionado;
} Navio;

typedef struct {
    Navio *listaNavios;
    int quantidade;
} Frota;

Frota criarFrota();
void destruirFrota(Frota* frota);
Navio* pegarNavio(Frota* frota, int id);
int verificarFrotaDestruida(Frota* frota);

#endif
