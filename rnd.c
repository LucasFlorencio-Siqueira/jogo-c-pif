#include "aleatorio.h"
#include <stdlib.h>
#include <time.h>

void iniciarAleatorio() {
    srand(time(NULL));
}

int gerarNumero(int min, int max) {
    return min + rand() % (max - min + 1);
}
