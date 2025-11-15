#include <stdio.h>
#include <unistd.h> 
#include "Display.h"
#include "board.h"

const char SMALLJ1 = 'x';
const char MEDIUMJ1 = 'X';
const char LARGEJ1 = '#';
const char SMALLJ2 = '.';
const char MEDIUMJ2 = 'o';
const char LARGEJ2 = 'O';
int Turnojugador;

player who_wins_diagonal(board game);
player who_wins_antidiagonal(board game);
player who_wins_column(board game, int col);
player who_wins_line(board game, int row);

void Tablero(board game) {
    printf("\n");

    for (int i = 0; i < DIMENSIONS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) { 
            char pieceHolder = get_place_holder(game, i, j);
            if (pieceHolder == NO_PLAYER) {
                printf("   ");  
            } else if (pieceHolder == PLAYER_1) {
                char pieceSize = get_piece_size(game, i, j);
                switch(pieceSize) {
                    case SMALL: printf(" %c ", SMALLJ1); break;
                    case MEDIUM: printf(" %c ", MEDIUMJ1); break;
                    case LARGE: printf(" %c ", LARGEJ1); break;
                }
            } else {
                char pieceSize = get_piece_size(game, i, j);
                switch(pieceSize) {
                    case SMALL: printf(" %c ", SMALLJ2); break;
                    case MEDIUM: printf(" %c ", MEDIUMJ2); break;
                    case LARGE: printf(" %c ", LARGEJ2); break;
                }   
            }

            if (j < DIMENSIONS -1) {
                printf(" | ");
            }
        }
        printf("\n");

        if (i < DIMENSIONS - 1) {
            printf("----+-----+----\n"); 
        }
    }
    printf("\n");
}

void Carcel(board game) {
    printf(" Player 1           Player 2\n");
    for (int s = SMALL; s <= LARGE; s++) {
        int NumCarcelJ1 = get_nb_piece_in_house(game, PLAYER_1, (size)s);
        int NumCarcelJ2 = get_nb_piece_in_house(game, PLAYER_2, (size)s);

        char PiezasJ1 = (s == SMALL) ? SMALLJ1 : ((s == MEDIUM) ? MEDIUMJ1 : LARGEJ1);
        char PiezasJ2 = (s == SMALL) ? SMALLJ2 : ((s == MEDIUM) ? MEDIUMJ2 : LARGEJ2);

        for (int i = 0; i < NumCarcelJ1; i++) {
            printf("%c", PiezasJ1); 
        }
        printf("           ");

        for (int i = 0; i < NumCarcelJ2; i++) {
            printf("%c", PiezasJ2); 
        }
        printf("\n");
    }  
}

int InteraccionMover(board game, player *current_player) {
    int NumEnCasa = 0;

    for (int s = SMALL; s <= LARGE; s++) {
        NumEnCasa += get_nb_piece_in_house(game, *current_player, (size)s);  
    }

    if (NumEnCasa > 5) {
        printf("Toutes tes pièces sont dans la maison. Tu ne peux pas déplacer.\n");
        sleep(2);
        return *current_player;   // ✔ FIX
    }

    int ColumnaI, FilaI;
    printf("Colonne ?\n");
    scanf("%d", &ColumnaI);
    printf("Fila ?\n");
    scanf("%d", &FilaI);
   

    if (ColumnaI < 0 || FilaI < 0 || ColumnaI >= DIMENSIONS || FilaI >= DIMENSIONS) {
        printf("Coordonnées invalides.\n");
        return *current_player;  
    }

    printf("Où veux-tu que la pièce finisse ?\n");
    int ColumnaF, FilaF;
    printf("Colonne ?\n");
    scanf("%d", &ColumnaF);
    printf("Fila ?\n");
    scanf("%d", &FilaF);

    if (ColumnaF < 0 || FilaF < 0 || ColumnaF >= DIMENSIONS || FilaF >= DIMENSIONS) {
        printf("Coordonnées invalides.\n");
        sleep(2);
        return *current_player;  
    }

    char pieceHolder = get_place_holder(game, FilaI, ColumnaI);
    if (pieceHolder != *current_player) {
        printf("Ce n'est pas ta pièce.\n");
        sleep(2);
        return *current_player;   
    }
    
    int res = move_piece(game, FilaI, ColumnaI, FilaF, ColumnaF);

    if (res == 0) {
        *current_player = next_player(*current_player);
    } else {
        printf("Error %d\n", res);
        sleep(2);
    }

    return *current_player;  // ✔ FIX
}


int InteraccionPlace(board game, player *current_player, int gobbler, int r, int c)
{
    printf("Quelle taille ? 0=Small, 1=Medium, 2=Large\n");

    int Tamano;
    scanf("%d", &Tamano);

    size piece_size = SMALL;
    if (Tamano == 1) piece_size = MEDIUM;
    if (Tamano == 2) piece_size = LARGE;

    int ColumnaF, FilaF;
    printf("Colonne ?\n");
    scanf("%d", &ColumnaF);
    printf("Fila ?\n");
    scanf("%d", &FilaF);

    if (gobbler == 1) {
        player winner = get_winner(game);
        if (winner == NO_PLAYER || winner == *current_player) {
            printf("Tu ne peux plus gober car il n'y a plus d'alignement adverse.\n");
            sleep(2);
            return *current_player;
        }

        if (ColumnaF != c || FilaF != r) {
            printf("Tu dois gober en (%d,%d) !\n", r, c);
            sleep(2);
            return *current_player;   
        }

        size pieza_objetivo = get_piece_size(game, r, c);
        if (piece_size <= pieza_objetivo) {
            printf("Ta pièce n'est pas assez grande pour gober !\n");
            sleep(2);
            return *current_player;
        }

        int res = place_piece(game, *current_player, piece_size, r, c);
        if (res == 0) {
            *current_player = next_player(*current_player);
        } else {
            printf("Erreur %d\n", res);
            sleep(2);
        }
        return *current_player;
    }

    if (ColumnaF < 0 || FilaF < 0 || ColumnaF >= DIMENSIONS || FilaF >= DIMENSIONS) {
        printf("Coordonnées invalides.\n");
        sleep(2);
        return *current_player;
    }

    size s_casilla = get_piece_size(game, FilaF, ColumnaF);

    if (s_casilla != NONE) {
        printf("Tu ne peux pas gober en mettant une pièce en jeu.\n");
        sleep(2);
        return *current_player;
    }

    int res = place_piece(game, *current_player, piece_size, FilaF, ColumnaF);
    if (res == 0) {
        *current_player = next_player(*current_player);
    } else {
        printf("Erreur %d\n", res);
        sleep(2);
    }

    return *current_player;
}

void TipoLinea(board game, LineType *tipo, int *posicion)
{
    player winner;

    winner = who_wins_diagonal(game);
    if (winner != NO_PLAYER) {
        *tipo = DIAGONAL;
        *posicion = -1;
        return;
    }

    winner = who_wins_antidiagonal(game);
    if (winner != NO_PLAYER) {
        *tipo = ANTIDIAGONAL;
        *posicion = -1;
        return;
    }

    for (int i = 0; i < DIMENSIONS; i++) {
        winner = who_wins_column(game, i);
        if (winner != NO_PLAYER) {
            *tipo = COLUMN;
            *posicion = i;
            return;
        }

        winner = who_wins_line(game, i);
        if (winner != NO_PLAYER) {
            *tipo = ROW;
            *posicion = i;
            return;
        }
    }

    *tipo = NO_LINE;
    *posicion = -1;
}


void BuscarGober(board game, LineType tipo, int pos, player ganador, int *row, int *col)
{
    player perdedor = (ganador == PLAYER_1 ? PLAYER_2 : PLAYER_1);

    for (int i = 0; i < 3; i++) {
        int r, c;

        if (tipo == DIAGONAL) {
            r = i; c = i;
        }
        else if (tipo == ANTIDIAGONAL) {
            r = i; c = 2 - i;
        }
        else if (tipo == ROW) {
            r = pos; c = i;
        }
        else if (tipo == COLUMN) {
            r = i; c = pos;
        } else {
            *row = -1;
            *col = -1;
            return;
        }

        size s = get_piece_size(game, r, c);

        if (s == SMALL) {
            if (get_nb_piece_in_house(game, perdedor, MEDIUM) > 0) { *row=r; *col=c; return; }
            if (get_nb_piece_in_house(game, perdedor, LARGE) > 0)  { *row=r; *col=c; return; }
        }

        if (s == MEDIUM) {
            if (get_nb_piece_in_house(game, perdedor, LARGE) > 0) { *row=r; *col=c; return; }
        }
    }

    *row = -1;
    *col = -1;
}


