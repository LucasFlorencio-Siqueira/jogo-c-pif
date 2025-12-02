#include "fleet.h"
#include <stdlib.h>
#include <string.h>

void inicializarFrota(Fleet* fleet) {
    fleet->count = 6;
    fleet->ships = (Ship*) malloc(fleet->count * sizeof(Ship));

    strcpy(fleet->ships[0].name, "Porta-Avioes");
    fleet->ships[0].length = 5;
    fleet->ships[0].hits = 0;
    fleet->ships[0].placed = 0;

    strcpy(fleet->ships[1].name, "Encouracado");
    fleet->ships[1].length = 4;
    fleet->ships[1].hits = 0;
    fleet->ships[1].placed = 0;

    strcpy(fleet->ships[2].name, "Cruzador A");
    fleet->ships[2].length = 3;
    fleet->ships[2].hits = 0;
    fleet->ships[2].placed = 0;

    strcpy(fleet->ships[3].name, "Cruzador B");
    fleet->ships[3].length = 3;
    fleet->ships[3].hits = 0;
    fleet->ships[3].placed = 0;

    strcpy(fleet->ships[4].name, "Destroyer A");
    fleet->ships[4].length = 2;
    fleet->ships[4].hits = 0;
    fleet->ships[4].placed = 0;

    strcpy(fleet->ships[5].name, "Destroyer B");
    fleet->ships[5].length = 2;
    fleet->ships[5].hits = 0;
    fleet->ships[5].placed = 0;
}

void liberarFrota(Fleet* fleet) {
    if (fleet->ships != NULL) {
        free(fleet->ships);
    }
}

Ship* pegarNavio(Fleet* fleet, int id) {
    if (id >= 0 && id < fleet->count) {
        return &fleet->ships[id];
    }
    return NULL;
}

int verificarFrotaDestruida(Fleet* fleet) {
    for (int i = 0; i < fleet->count; i++) {
        if (fleet->ships[i].hits < fleet->ships[i].length) {
            return 0;
        }
    }
    return 1;
}
