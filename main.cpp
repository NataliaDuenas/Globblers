#include <cstdio>
#include <unistd.h>

#include "board.h"
#include "Display.h"
#include "enums.h"

int main() {
    Board game;
    std::printf("Le jeu commence\n");

    int Turnojugador;
    LineType tipo;
    int pos;
    Player ganador = Player::NO_PLAYER;

    std::printf("Commence jouer 1\n");
    Player current_player = Player::PLAYER_1;

    Tablero(game);
    Carcel(game);

    while (true) {
        Player possible_winner = game.getWinner();

        int gobbler = 0;
        int r = -1, c = -1;

        if (possible_winner != Player::NO_PLAYER) {
            if (possible_winner != current_player) {

                game.tipoLinea(tipo, pos);
                bool ok = game.buscarGober(tipo, pos, possible_winner, r, c);

                if (ok) {
                    gobbler = 1;
                    std::printf("Le perdant DOIT gober en (%d,%d) !\n", r, c);
                } else {
                    ganador = possible_winner;
                    break;
                }

            } else {
                ganador = possible_winner;
                break;
            }
        }

        std::printf("1) Move    2) Place\n");
        int MoveOuPlace;
        std::scanf("%d", &MoveOuPlace);

        if (MoveOuPlace == 1) {
            if (gobbler == 1) {
                std::printf("Tu dois gober, tu ne peux pas déplacer.\n");
                sleep(2);
                continue;
            }
            Turnojugador = InteraccionMover(game, current_player); // <- sin &
        }
        else if (MoveOuPlace == 2) {
            Turnojugador = InteraccionPlace(game, current_player, gobbler, r, c);
        }
        else {
            std::printf("Doit choisir entre 1 et 2\n");
            sleep(2);
            continue;
        }

        Tablero(game);

        if ((Player)Turnojugador == Player::PLAYER_1)
            std::printf("C'est au tour du joueur 1\n");
        else
            std::printf("C'est au tour du joueur 2\n");

        Carcel(game);
    }

    std::printf("Le jeu a terminé\n");
    sleep(2);

    if (ganador == Player::PLAYER_1)
        std::printf("Le gagnant est le joueur 1\n");
    else if (ganador == Player::PLAYER_2)
        std::printf("Le gagnant est le joueur 2\n");
    else
        std::printf("Match nul\n");

    return 0;
}
