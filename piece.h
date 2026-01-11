#ifndef PIECE_H
#define PIECE_H

#include "enums.h"

class Piece {
private:
    Player owner;
    Size size;

public:
    // Constructeur par défaut : crée une pièce vide
    Piece() : owner(Player::NO_PLAYER), size(Size::NONE) {}

    // Constructeur permettant d'initialiser la pièce avec un joueur et une taille
    Piece(Player owner, Size size) : owner(owner), size(size) {}

    // Accesseurs simples (fonctions inline) définis dans le fichier .h
    Player getOwner() const { return owner; }
    Size getSize() const { return size; }
};

#endif
