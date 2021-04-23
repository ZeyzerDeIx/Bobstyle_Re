#include "Game.h"

using namespace std;

int game(Global_variables_container* GVC)
{
    bool done = false; //sert a maintenir la boucle principale

    Timer timer; //sert � mesurer le temps

    Bobstyle bobstyle(GVC); //cr�ation de bobstyle (le personnage jouable)

    Interface interface_guy(GVC, &bobstyle, &done); //c'est l'interface

    Generator generate_guy(GVC); //c'est le g�n�rateur
    generate_guy.set_auto_generation(true); //on le met en mode automatique (il g�n�re selon la difficult�)

    Handler handle_guy(GVC, &bobstyle, &interface_guy, &generate_guy, &done); //sert � gerer les entr�s du joueur

    //boucle principale
    while (!done)
    {
        if(timer.get_elapsed_time() >= MILISEC_PER_FRAME)
        {
            timer.restart();

            GVC->update_frame(); //permet de tenir le compte des frame depuis le d�but de la partie

            generate_guy.manage_collisions(&bobstyle);
            if(!bobstyle.get_parameter(ALIVE))
            {
                done = true;
            }

            //gestion de l'affichage et autres
            //{
                //rebouter l'�cran en bleu
                SDL_SetRenderDrawColor(GVC->renderer(), BACK_SCREEN_COLOR_R, BACK_SCREEN_COLOR_G, BACK_SCREEN_COLOR_B, 0);
                SDL_RenderFillRect(GVC->renderer(), nullptr);

                //ici on affiche les entit�s
                //{
                    generate_guy.manage_and_display();

                    bobstyle.manage_and_display();
                //}

                interface_guy.display();

                //On actualise l'�cran
                SDL_RenderPresent(GVC->renderer());

            //}
            //Fin de la gestion de l'affichage et autres
        }

        handle_guy.handle(); //on g�re les entr�s du joueur

        //On laisse le temps au CPU de faire autre chose
        SDL_Delay(1);

    } //fin de la boucle principale

    GVC->reset_frame(); //on reset le compteur de frame

    save(enter_text(GVC), interface_guy.get_score()); //en travaux

    return 0;
}
