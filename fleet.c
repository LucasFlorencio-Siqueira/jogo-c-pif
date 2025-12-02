#include "fleet.h"
#include <stdlib.h>
#include <string.h>

Frota criarFrota() {
    Frota f;
    f.quantidade = 6;
    f.listaNavios = (Navio*) malloc(f.quantidade * sizeof(Navio));

    strcpy(f.listaNavios[0].nome, "Porta-Avioes");
    f.listaNavios[0].tamanho = 5;
    f.listaNavios[0].acertos = 0;
    f.listaNavios[0].posicionado = 0;

    strcpy(f.listaNavios[1].nome, "Encouracado");
    f.listaNavios[1].tamanho = 4;
    f.listaNavios[1].acertos = 0;
    f.listaNavios[1].posicionado = 0;

    strcpy(f.listaNavios[2].nome, "Cruzador A");
    f.listaNavios[2].tamanho = 3;
    f.listaNavios[2].acertos = 0;
    f.listaNavios[2].posicionado = 0;

    strcpy(f.listaNavios[3].nome, "Cruzador B");
    f.listaNavios[3].tamanho = 3;
    f.listaNavios[3].acertos = 0;
    f.listaNavios[3].posicionado = 0;

    strcpy(f.listaNavios[4].nome, "Destroyer A");
    f.listaNavios[4].tamanho = 2;
    f.listaNavios[4].acertos = 0;
    f.listaNavios[4].posicionado = 0;

    strcpy(f.listaNavios[5].nome, "Destroyer B");
    f.listaNavios[5].tamanho = 2;
    f.listaNavios[5].acertos = 0;
    f.listaNavios[5].posicionado = 0;

    return f;
}

void destruirFrota(Frota* frota) {
    if (frota->listaNavios != NULL) {
        free(frota->listaNavios);
    }
}

Navio* pegarNavio(Frota* frota, int id) {
    if (id >= 0 && id < frota->quantidade) {
        return &frota->listaNavios[id];
    }
    return NULL;
}

int verificarFrotaDestruida(Frota* frota) {
    for (int i = 0; i < frota->quantidade; i++) {
        if (frota->listaNavios[i].acertos < frota->listaNavios[i].tamanho) {
            return 0;
        }
    }
    return 1;
}
