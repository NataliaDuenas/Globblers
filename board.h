#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "enums.h"

constexpr int DIMENSIONS = 3;
constexpr int NB_INITIAL_PIECES = 2;

class Board {
private:
    Cell grid[DIMENSIONS][DIMENSIONS];

    int house[3][4]; // Carcel de ambos jugadores sin utiliza [0]

    bool validCoord(int x) const { return x >= 0 && x < DIMENSIONS; }
    bool validPlayer(Player p) const { return p == Player::PLAYER_1 || p == Player::PLAYER_2; }
    bool validSize(Size s) const { return s == Size::SMALL || s == Size::MEDIUM || s == Size::LARGE; }

public:
    Board();

    Player nextPlayer(Player p) const;

    Player getPlaceHolder(int line, int col) const;
    Size getPieceSize(int line, int col) const;

    int getNbPieceInHouse(Player p, Size s) const;

    Status placePiece(Player p, Size s, int line, int col);
    Status movePiece(int sl, int sc, int tl, int tc);

    Player getWinner() const;

    Player winsRow(int r) const;
    Player winsCol(int c) const;
    Player winsDiag() const;
    Player winsAntiDiag() const;

    void tipoLinea(LineType& tipo, int& posicion) const;
    bool buscarGober(LineType tipo, int pos, Player ganador, int& row, int& col) const;

};

#endif
