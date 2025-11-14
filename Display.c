#include <stdio.h>
#include "board.h"

const char SMALLJ1 = 'x';
const char MEDIUMJ1 = 'X';
const char LARGEJ1 = '#';
const char SMALLJ2 = '.';
const char MEDIUMJ2 = 'o';
const char LARGEJ2 = 'O';

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
            printf("---+---+---\n"); 
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
        return;  
    }

    int ColumnaI, FilaI;
    printf("Colonne ?\n");
    scanf("%d", &ColumnaI);
    printf("Fila ?\n");
    scanf("%d", &FilaI);

    // Validación de coordenadas
    if (ColumnaI < 0 || FilaI < 0 || ColumnaI >= DIMENSIONS || FilaI >= DIMENSIONS) {
        printf("Doit choisir entre le tableau de %dx%d\n", DIMENSIONS, DIMENSIONS);
        return;  
    }

    printf("Où veux-tu que la pièce finisse ?\n");
    int ColumnaF, FilaF;
    printf("Colonne ?\n");
    scanf("%d", &ColumnaF);
    printf("Fila?\n");
    scanf("%d", &FilaF);

    // Validación de coordenadas de destino
    if (ColumnaF < 0 || FilaF < 0 || ColumnaF >= DIMENSIONS || FilaF >= DIMENSIONS) {
        printf("Doit bouger entre le tableau de %dx%d\n", DIMENSIONS, DIMENSIONS);
        return;  
    }

    // Verificar que el jugador tenga una pieza en la posición inicial
    char pieceHolder = get_place_holder(game, FilaI, ColumnaI);
    if (pieceHolder == *current_player) {
        int res = move_piece(game, FilaI, ColumnaI, FilaF, ColumnaF);
        if (res == 0) {
            return 0;
        } else {
            printf("Error %d\n", res);
            return 1;
        }
    } else {
        printf("Ce n'est pas ta pièce\n");
        return 1;
    }      
}

int InteraccionPlace(board game, player *current_player) {
    printf("Quelle taille de pièce que tu voudras bouger ?\n");
    printf("0) Small     1) Medium       2) Large\n");

    int Tamano;
    scanf("%d", &Tamano);

    // Mapear entrada a la enumeración de tamaños
    size piece_size;
    switch (Tamano) {
        case 0: piece_size = SMALL; break;
        case 1: piece_size = MEDIUM; break;
        case 2: piece_size = LARGE; break;
        default:
            printf("Choix invalide. Taille SMALL.\n");
            piece_size = SMALL;
    }

    int ColumnaF,FilaF;
    printf("Où veux-tu que la pièce finisse ?\n");
    printf("Colonne ?\n");
    scanf("%d ", &ColumnaF);
    printf("Fila ?\n");
    scanf("%d ", &FilaF);

    // Validación de coordenadas
    if (ColumnaF < 0 || FilaF < 0 || ColumnaF >= DIMENSIONS || FilaF >= DIMENSIONS) {
        printf("Doit bouger entre le tableau de %dx%d\n", DIMENSIONS, DIMENSIONS);
        return;  
    }

    char pieceHolder = get_place_holder(game, FilaI, ColumnaI);
    player opponent = (*current_player == PLAYER_1) ? PLAYER_2 : PLAYER_1;

    if(pieceHolder==NO_PLAYER){
        int res = place_piece(game, *current_player, piece_size, FilaF, ColumnaF);
        switch (res) {
            case 0: 
                return 0; 
                break;
            case 1: 
                printf("Erreur : La pièce n'est pas disponible dans la maison du joueur.\n"); 
                return 1; 
                break;
            case 2: 
                printf("Erreur : La pièce est trop petite pour être placée à cet endroit.\n"); 
                return 1;
                break;
            case 3: 
                printf("Erreur : Coordonnées illégales. Essayez encore.\n");
                return 1;
                break;
            default:  
                printf("Erreur inconnue.\n");
                return 1;
        }
    }else if(pieceHolder==opponent){
        ganador = get_winner(game);
        if(ganador==pieceHolder){
           

        } else{printf("Ne gober en mettant une pièce en jeu");
        return; }
        
    } else{printf("Ne gober en mettant une pièce en jeu");
        return; }
 
}
