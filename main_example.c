#include <stdio.h>
#include <unistd.h>  
#include "board.h"
#include "Display.h"  

int main() 
{
    board game = new_game();
    printf("Le jeu commence\n");

    int Turnojugador;
    LineType tipo;
    int pos;
    int ganador = NO_PLAYER;

    printf("Commence jouer 1\n");
    player current_player = PLAYER_1;

    Tablero(game);     
    Carcel(game);  

    while (1) 
    {
        player possible_winner = get_winner(game);

        int gobbler = 0;
        int r = -1, c = -1;

        if (possible_winner != NO_PLAYER) 
        {
            if (possible_winner != current_player) 
            {
                TipoLinea(game, &tipo, &pos);

                BuscarGober(game, tipo, pos, possible_winner, &r, &c);

                if (r != -1) 
                {
                    gobbler = 1;  
                    printf("Le perdant DOIT gober en (%d,%d) !\n", r, c);
                } 
                else 
                {
                    ganador = possible_winner;
                    break; 
                }
            } 
            else 
            {
                ganador = possible_winner;
                break;
            }
        }

        printf("1) Move    2) Place\n");
        int MoveOuPlace;
        scanf("%d", &MoveOuPlace); 

        if (MoveOuPlace == 1) 
        {
            if (gobbler == 1) 
            {
                printf("Tu dois gober, tu ne peux pas déplacer.\n");
                sleep(2);
                continue;
            }

            Turnojugador = InteraccionMover(game, &current_player); 
        }
        else if (MoveOuPlace == 2) 
        {
            Turnojugador = InteraccionPlace(game, &current_player, gobbler, r, c);
        } 
        else 
        {
            printf("Doit choisir entre 1 et 2\n"); 
            sleep(2); 
            continue;
        }

        Tablero(game);   

        if (Turnojugador == PLAYER_1) 
            printf("C'est au tour du joueur 1\n");
        else 
            printf("C'est au tour du joueur 2\n");

        Carcel(game); 

    }

    printf("Le jeu a terminé\n");
    sleep(2);

    if (ganador == PLAYER_1) {
        printf("Le gagnant est le joueur 1\n");
    } 
    else if (ganador == PLAYER_2) {
        printf("Le gagnant est le joueur 2\n");
    } 
    else {
        printf("Match nul\n");
    }

    destroy_game(game);
    return 0;
}
