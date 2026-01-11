#include <cstdio>
#include <unistd.h>
#include "Display.h"

const char SMALLJ1  = 'x';
const char MEDIUMJ1 = 'X';
const char LARGEJ1  = '#';
const char SMALLJ2  = '.';
const char MEDIUMJ2 = 'o';
const char LARGEJ2  = 'O';

void Tablero(const Board& game) {
    std::printf("\n");

    for (int i = 0; i < DIMENSIONS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {

            Player pieceHolder = game.getPlaceHolder(i, j);

            if (pieceHolder == Player::NO_PLAYER) {
                std::printf("   ");
            } else {
                Size pieceSize = game.getPieceSize(i, j);

                char c = ' ';
                if (pieceHolder == Player::PLAYER_1) {
                    if (pieceSize == Size::SMALL)  c = SMALLJ1;
                    if (pieceSize == Size::MEDIUM) c = MEDIUMJ1;
                    if (pieceSize == Size::LARGE)  c = LARGEJ1;
                } else {
                    if (pieceSize == Size::SMALL)  c = SMALLJ2;
                    if (pieceSize == Size::MEDIUM) c = MEDIUMJ2;
                    if (pieceSize == Size::LARGE)  c = LARGEJ2;
                }
                std::printf(" %c ", c);
            }

            if (j < DIMENSIONS - 1)
                std::printf("|");
        }
        std::printf("\n");

        if (i < DIMENSIONS - 1)
            std::printf("----+-----+----\n");
    }
    std::printf("\n");
}

void Carcel(const Board& game) {
    std::printf(" Player 1           Player 2\n");

    for (int s = (int)Size::SMALL; s <= (int)Size::LARGE; s++) {
        Size size = (Size)s;

        int NumCarcelJ1 = game.getNbPieceInHouse(Player::PLAYER_1, size);
        int NumCarcelJ2 = game.getNbPieceInHouse(Player::PLAYER_2, size);

        char PiezasJ1 = (size == Size::SMALL)  ? SMALLJ1 :
                        (size == Size::MEDIUM) ? MEDIUMJ1 : LARGEJ1;

        char PiezasJ2 = (size == Size::SMALL)  ? SMALLJ2 :
                        (size == Size::MEDIUM) ? MEDIUMJ2 : LARGEJ2;

        for (int i = 0; i < NumCarcelJ1; i++)
            std::printf("%c", PiezasJ1);

        std::printf("           ");

        for (int i = 0; i < NumCarcelJ2; i++)
            std::printf("%c", PiezasJ2);

        std::printf("\n");
    }
}


int InteraccionMover(Board& game, Player& current_player) {
    int NumEnCasa = 0;

    for (int s = (int)Size::SMALL; s <= (int)Size::LARGE; ++s)
        NumEnCasa += game.getNbPieceInHouse(current_player, (Size)s);

    if (NumEnCasa > 5) {
        std::printf("Toutes tes pièces sont dans la maison. Tu ne peux pas déplacer.\n");
        sleep(2);
        return (int)current_player;
    }

    int ColumnaI, FilaI;
    std::printf("Colonne ?\n");
    std::scanf("%d", &ColumnaI);
    std::printf("Ligne ?\n");
    std::scanf("%d", &FilaI); 
   

    if (ColumnaI < 0 || FilaI < 0 || ColumnaI >= DIMENSIONS || FilaI >= DIMENSIONS) {
        std::printf("Coordonnées invalides.\n");
        sleep(2);
        return (int)current_player;
    }

    std::printf("Où veux-tu que la pièce finisse ?\n");
    int ColumnaF, FilaF;
    std::printf("Colonne destination ?\n");
    std::scanf("%d", &ColumnaF);
    std::printf("Ligne destination ?\n");
    std::scanf("%d", &FilaF);

    if (ColumnaF < 0 || FilaF < 0 || ColumnaF >= DIMENSIONS || FilaF >= DIMENSIONS) {
        std::printf("Coordonnées invalides.\n");
        sleep(2);
        return (int)current_player;
    }

    Player pieceHolder = game.getPlaceHolder(FilaI, ColumnaI);
    if (pieceHolder != current_player) {                       
        std::printf("Ce n'est pas ta pièce.\n");
        sleep(2);
        return (int)current_player;
    }
    
     Status res = game.movePiece(FilaI, ColumnaI, FilaF, ColumnaF);

    if (res == Status::OK) {
        current_player = game.nextPlayer(current_player);
    } else {
        std::printf("Déplacement impossible.\n");
        sleep(2);
    }

    return (int)current_player;
}


int InteraccionPlace(Board& game, Player& current_player, int gobbler, int r, int c) {
    std::printf("Quelle taille ? 0=Small, 1=Medium, 2=Large\n");

    int Tamano;
    std::scanf("%d", &Tamano);

    Size piece_size = (Tamano == 0) ? Size::SMALL :
                      (Tamano == 1) ? Size::MEDIUM : Size::LARGE;

    int ColumnaF, FilaF;
    std::printf("Colonne ?\n");
    std::scanf("%d", &ColumnaF);
    std::printf("Ligne ?\n");
    std::scanf("%d", &FilaF);


//Lógica obligar a gobbler
    if (gobbler == 1) {
       Player winner = game.getWinner();

         if (winner == Player::NO_PLAYER || winner == current_player) {
            std::printf("Tu ne peux plus gober car il n'y a plus d'alignement adverse.\n");
            sleep(2);
            return (int)current_player;
        }

        if (ColumnaF != c || FilaF != r) {
            std::printf("Tu dois gober en (%d,%d) !\n", r, c);
            sleep(2);
            return (int)current_player;
        }

        Size pieza_objetivo = game.getPieceSize(r, c);
        if ((int)piece_size <= (int)pieza_objetivo) {
            std::printf("Ta pièce n'est pas assez grande pour gober !\n");
            sleep(2);
            return (int)current_player;
        }

        Status res = game.placePiece(current_player, piece_size, r, c);
        if (res == Status::OK) {
            current_player = game.nextPlayer(current_player);
        } else {
            std::printf("Erreur %d\n", (int)res);
            sleep(2);
        }
        return (int)current_player;
    }


    if (ColumnaF < 0 || FilaF < 0 || ColumnaF >= DIMENSIONS || FilaF >= DIMENSIONS) {
        std::printf("Coordonnées invalides.\n");
        sleep(2);
        return (int)current_player;
    }

    Size s_casilla = game.getPieceSize(FilaF, ColumnaF);
    if (s_casilla != Size::NONE) {
        std::printf("Tu ne peux pas gober en mettant une pièce en jeu.\n");
        sleep(2);
        return (int)current_player;
    }

    Status res = game.placePiece(current_player, piece_size, FilaF, ColumnaF);
    if (res == Status::OK) {
        current_player = game.nextPlayer(current_player);
    } else {
        std::printf("Erreur %d\n", (int)res);
        sleep(2);
    }

    return (int)current_player;
}


