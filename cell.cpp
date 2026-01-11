#include "cell.h"

Cell::Cell() {
    for (int i = 0; i < 4; ++i) {
        layers[i] = Piece();
    }
}

Size Cell::topSize() const {
    if (layers[(int)Size::LARGE].getSize() != Size::NONE)  return Size::LARGE;
    if (layers[(int)Size::MEDIUM].getSize() != Size::NONE) return Size::MEDIUM;
    if (layers[(int)Size::SMALL].getSize() != Size::NONE)  return Size::SMALL;
    return Size::NONE;
}

Player Cell::topOwner() const {
    Size s = topSize();
    if (s == Size::NONE) return Player::NO_PLAYER;
    return layers[(int)s].getOwner();
}

bool Cell::canPlace(Size s) const {
    if (s == Size::NONE) return false;
    return (int)s > (int)topSize();
}

void Cell::place(Player p, Size s) {
    layers[(int)s] = Piece(p, s);
}

bool Cell::hasTop() const {
    return topSize() != Size::NONE;
}

Piece Cell::takeTop() {
    Size s = topSize();
    if (s == Size::NONE) return Piece();

    Piece removed = layers[(int)s];
    layers[(int)s] = Piece();
    return removed;
}
