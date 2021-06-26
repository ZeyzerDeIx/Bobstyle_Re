#include "Debug_room.h"

using namespace std;

int debug_room(Global_variables_container* GVC)
{
    bool done = false; //sert a maintenir la boucle principale

    Timer timer; //sert � mesurer le temps

    Timer cooldown; //pour tirer

    Bobstyle bobstyle(GVC, "sprites/DEBUG/AnimatedDebugRect.bmp", 9); //cr�ation de bobstyle (le personnage jouable)
    bobstyle.set_parameter(BOOMERANG, true);
    bobstyle.set_parameter(DEBUG_MODE, true);

    Interface interface_guy(GVC, &bobstyle, &done); //c'est l'interface
    interface_guy.set_parameter(DEBUG_MODE, true);

    Generator generate_guy(GVC, &bobstyle); //c'est le g�n�rateur
    generate_guy.set_clouds(false); //on d�sactiveles nuages
    generate_guy.set_debug_mode(true); //on active le debug mode
    //generate_guy.set_auto_generation(true); //on le met en mode automatique (il g�n�re selon la difficult�)

    Handler handle_guy(GVC, &bobstyle, &interface_guy, &generate_guy, &done); //sert � gerer les entr�s du joueur

    Kube test_boss(GVC, &bobstyle, &generate_guy);
    test_boss.set_parameter(DEBUG_MODE, true);

    //boucle principale
    while (!done)
    {
        if(timer.get_elapsed_time() >= MILISEC_PER_FRAME)
        {
            timer.restart();

            GVC->update_frame(); //permet de tenir le compte des frame depuis le d�but de la partie

            generate_guy.manage_collisions(&bobstyle);

            //gestion de l'affichage et autres
            //{
                //rebouter l'�cran en bleu
                SDL_SetRenderDrawColor(GVC->renderer(), BACK_SCREEN_COLOR_R, BACK_SCREEN_COLOR_G, BACK_SCREEN_COLOR_B, 0); //on choisit la couleur
                SDL_RenderFillRect(GVC->renderer(), 0); //on en remplit l'�cran

                //ici on affiche les entit�s
                //{
                    generate_guy.manage_and_display();

                    test_boss.manage_and_display();

                    bobstyle.manage_and_display();
                //}

                /*if(cooldown.get_elapsed_time() >= 1000)
                {
                    test_weapon.fire();
                    //generate_guy.generate_entities(PROJECTILE,640,512,&bobstyle);
                    cooldown.restart();
                }*/

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

    //save(enter_text(GVC), interface_guy.get_score()); //en travaux

    return 0;
}
