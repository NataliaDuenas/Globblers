#ifndef CELL_H
#define CELL_H

#include "piece.h"
#include "enums.h"

class Cell{
private: 
    Piece layers[4];

public:
    Cell();

    Size topSize() const;
    Player topOwner() const;
    
    bool canPlace(Size s) const;
    void place(Player p, Size s);

    bool hasTop() const;
    Piece takeTop();
};

#endif 