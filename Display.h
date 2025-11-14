#ifndef H_DISPLAY
#define H_DISPLAY
#include <stdio.h>
#include "board.h"

   void Tablero(board game);
   void Carcel(board game);
   void InteraccionMover(board game, player *current_player);
   void InteraccionPlace(board game, player *current_player);
#endif