#ifndef DISPLAY_H
#define DISPLAY_H

#include "board.h"

typedef enum {
    NO_LINE = 0,
    DIAGONAL,
    ANTIDIAGONAL,
    ROW,
    COLUMN
} LineType;

void Tablero(board game);
void Carcel(board game);
int InteraccionMover(board game, player *current_player);
int InteraccionPlace(board game, player *current_player, int gobbler, int r, int c);

void TipoLinea(board game, LineType *tipo, int *posicion);
void BuscarGober(board game, LineType tipo, int pos, player ganador, int *row, int *col);

#endif
