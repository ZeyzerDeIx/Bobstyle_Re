#include "constants.h"
#include "usefull_fonctions.h"
#include "Menu.h"

using namespace std;

int main(int argv, char** argsc)
{
    SDL_Delay(500);
    Menu menu(start_SDL(), 4);
    menu.set_button(1, F_GAME, "Jouer");
    menu.set_button(2, F_OPTIONS, "Options");
    menu.set_button(3, F_SCORES_TABLE, "Table des scores");
    menu.set_button(4, F_QUIT, "Quitter");
    menu.set_caption("Menu principal");

    menu.set_parameter(IS_MAIN_MENU, true);

    return menu.start();
}
