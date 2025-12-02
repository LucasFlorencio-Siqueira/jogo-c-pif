#ifndef FLEET_H
#define FLEET_H

typedef enum { ORIENT_H, ORIENT_V } Orientation;

typedef struct {
    char name[20];
    int length;
    int hits;
    int placed;
} Ship;

typedef struct {
    Ship *ships;
    int count;
} Fleet;

void inicializarFrota(Fleet* fleet);
void liberarFrota(Fleet* fleet);
Ship* pegarNavio(Fleet* fleet, int id);
int verificarFrotaDestruida(Fleet* fleet);

#endif
