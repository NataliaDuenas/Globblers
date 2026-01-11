#include "board.h"


Board::Board() {
    for (int p = 0; p < 3; ++p) {
        for (int s = 0; s < 4; ++s) {
            house[p][s] = 0;
        }
    }
    house[(int)Player::PLAYER_1][(int)Size::SMALL]  = NB_INITIAL_PIECES;
    house[(int)Player::PLAYER_1][(int)Size::MEDIUM] = NB_INITIAL_PIECES;
    house[(int)Player::PLAYER_1][(int)Size::LARGE]  = NB_INITIAL_PIECES;

    house[(int)Player::PLAYER_2][(int)Size::SMALL]  = NB_INITIAL_PIECES;
    house[(int)Player::PLAYER_2][(int)Size::MEDIUM] = NB_INITIAL_PIECES;
    house[(int)Player::PLAYER_2][(int)Size::LARGE]  = NB_INITIAL_PIECES;
}

Player Board::nextPlayer(Player p) const {
    if (p == Player::PLAYER_1) return Player::PLAYER_2;
    if (p == Player::PLAYER_2) return Player::PLAYER_1;
    return Player::NO_PLAYER;
}

Player Board::getPlaceHolder(int line, int col) const {
    if (!validCoord(line) || !validCoord(col)) return Player::NO_PLAYER;
    return grid[line][col].topOwner();
}

Size Board::getPieceSize(int line, int col) const {
    if (!validCoord(line) || !validCoord(col)) return Size::NONE;
    return grid[line][col].topSize();
}

int Board::getNbPieceInHouse(Player p, Size s) const {
    if (!validPlayer(p) || !validSize(s)) return 0;
    return house[(int)p][(int)s];
}

Status Board::placePiece(Player p, Size s, int line, int col) {
    if (!validPlayer(p) || !validSize(s) || !validCoord(line) || !validCoord(col))
        return Status::INVALID_ENTRY;

    if (house[(int)p][(int)s] <= 0)
        return Status::INVALID_SOURCE;

    if (!grid[line][col].canPlace(s))
        return Status::INVALID_TARGET;

    grid[line][col].place(p, s);
    house[(int)p][(int)s]--;
    return Status::OK;
}

Status Board::movePiece(int sl, int sc, int tl, int tc) {
    if (!validCoord(sl) || !validCoord(sc) || !validCoord(tl) || !validCoord(tc))
        return Status::INVALID_ENTRY;

    Cell& source = grid[sl][sc];
    Cell& target = grid[tl][tc];

    // Revisar que hay algo en la casilla
    if (source.topSize() == Size::NONE)
        return Status::INVALID_SOURCE;

    Size movingSize = source.topSize(); // Tamaño de la pieza que quiere mover

    if (!target.canPlace(movingSize)) // Compara la pieza en la casilla target y la que quiere mover
        return Status::INVALID_TARGET;

    Piece moved = source.takeTop();
    target.place(moved.getOwner(), moved.getSize());

    return Status::OK;
}

Player Board::winsRow(int r) const {
    Player a = getPlaceHolder(r, 0); //Toma la primera casilla
    if (a == Player::NO_PLAYER) return Player::NO_PLAYER; //Si no hay jugador sale 
    if (a == getPlaceHolder(r, 1) && a == getPlaceHolder(r, 2)) return a; //Revisa que el jugador sea el mismo en las tres
    return Player::NO_PLAYER;
}

Player Board::winsCol(int c) const {
    Player a = getPlaceHolder(0, c);
    if (a == Player::NO_PLAYER) return Player::NO_PLAYER;
    if (a == getPlaceHolder(1, c) && a == getPlaceHolder(2, c)) return a;
    return Player::NO_PLAYER;
}

Player Board::winsDiag() const {
    Player a = getPlaceHolder(0, 0);
    if (a == Player::NO_PLAYER) return Player::NO_PLAYER;
    if (a == getPlaceHolder(1, 1) && a == getPlaceHolder(2, 2)) return a;
    return Player::NO_PLAYER;
}

Player Board::winsAntiDiag() const {
    Player a = getPlaceHolder(0, 2);
    if (a == Player::NO_PLAYER) return Player::NO_PLAYER;
    if (a == getPlaceHolder(1, 1) && a == getPlaceHolder(2, 0)) return a;
    return Player::NO_PLAYER;
}

Player Board::getWinner() const {
    bool p1 = false, p2 = false;

    for (int i=0; i < DIMENSIONS; i++){
        Player r = winsRow(i);
        if (r == Player::PLAYER_1)  p1 = true;
        if (r == Player::PLAYER_2)  p2 = true;
        
        Player c = winsCol(i);
        if (c == Player::PLAYER_1)  p1 = true;
        if (c == Player::PLAYER_2)  p2 = true;
    }

    Player d= winsDiag();
    if (d == Player::PLAYER_1) p1 = true;
    if (d == Player::PLAYER_2) p2 = true;

    Player ad= winsAntiDiag();
    if (ad == Player::PLAYER_1) p1 = true;
    if (ad == Player::PLAYER_2) p2 = true;
    
    if (p1 && !p2) return Player::PLAYER_1;
    if (p2 && !p1) return Player::PLAYER_2;
    return Player::NO_PLAYER; // ninguno o ambos
}

 void Board::tipoLinea(LineType& tipo, int& posicion) const {
    Player winner;

    winner = winsDiag();
    if (winner != Player::NO_PLAYER) {
        tipo = LineType::DIAGONAL;
        posicion = -1;
        return;
    }

    winner = winsAntiDiag();
    if (winner != Player::NO_PLAYER) {
        tipo = LineType::ANTIDIAGONAL;
        posicion = -1;
        return;
    }

    for (int i = 0; i < DIMENSIONS; ++i) {
        winner = winsCol(i);
        if (winner != Player::NO_PLAYER) {
            tipo = LineType::COLUMN;
            posicion = i;
            return;
        }

        winner = winsRow(i);
        if (winner != Player::NO_PLAYER) {
            tipo = LineType::ROW;
            posicion = i;
            return;
        }
    }

    tipo = LineType::NO_LINE;
    posicion = -1;
}


 bool Board::buscarGober(LineType tipo, int pos, Player ganador, int& row, int& col) const {
    Player perdedor =
        (ganador == Player::PLAYER_1) ? Player::PLAYER_2 : Player::PLAYER_1;

    for (int i = 0; i < DIMENSIONS; ++i) {
        int r, c;

        if (tipo == LineType::DIAGONAL) {
            r = i; c = i;
        } else if (tipo == LineType::ANTIDIAGONAL) {
            r = i; c = DIMENSIONS - 1 - i;
        } else if (tipo == LineType::ROW) {
            r = pos; c = i;
        } else if (tipo == LineType::COLUMN) {
            r = i; c = pos;
        } else {
            return false;
        }

        Size s = getPieceSize(r, c);

        if (s == Size::SMALL) {
            if (getNbPieceInHouse(perdedor, Size::MEDIUM) > 0 ||
                getNbPieceInHouse(perdedor, Size::LARGE) > 0) {
                row = r; col = c; return true;
            }
        }

        if (s == Size::MEDIUM) {
            if (getNbPieceInHouse(perdedor, Size::LARGE) > 0) {
                row = r; col = c; return true;
            }
        }
    }
    return false;
}

