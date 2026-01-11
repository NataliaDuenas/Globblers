#ifndef DISPLAY_H
#define DISPLAY_H

#include "board.h"
#include "enums.h"

void Tablero(const Board& game);
void Carcel(const Board& game);

int InteraccionMover(Board& game, Player& current_player);
int InteraccionPlace(Board& game, Player& current_player, int gobbler, int r, int c);

#endif
