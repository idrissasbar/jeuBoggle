#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include"de.h"
typedef struct{
    int num;  // chaque partie a un numero
    Grille grille[4][4];
    int selectX;
    int selectY;
    int level;///
}Grid;

void init_grille_admin(Grid *admin_grid);
#endif // GRID_H_INCLUDED
