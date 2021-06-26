#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

    #include "constants.h"
    #include "Game.h"
    #include "Debug_room.h"
    #include "Button.h"
    #include "Timer.h"

    class Menu
    {
        public:

            Menu(Global_variables_container* GVC, int button_number = 0, int column_number = 1, Sprite* screenshot = 0);
            ~Menu();

            int start(); //lance le menu

            virtual void display(); //affiche le contenu du menu
            virtual void click(int up_or_down = DOWN); //informe les bouton que le joueur a cliqu�

            //permet de d�finir un bouton, son utilit� et son texte
            void set_button(int which_button, int which_function = F_QUIT, std::string new_text = "SAME", int wich_slot = 0);

            //permet d'ajouter une seconde fonction quand le bouton a d�j� �t� cliqu�
            void add_button_function(int which_button, int which_function = F_QUIT, std::string new_text = "SAME");

            void set_caption(std::string new_text); //permet de changer le titre du menu
            void set_parameter(int which_parameter, bool enable); //permet de modifier le param�tre de notre choix

            /*Permet aux boutons d'appeler un fonction d�finie parmis les valeurs suivantes:
            * F_QUIT: Met fin au menu, le quitte
            * F_GAME: Lance une partie
            * F_OPTIONS: Cr�er un menu "options"
            * F_DIFFICULTY_CHOICE: Cr�er un menu de selection de difficult�
            * F_SET_DIFFICULTY: Permet de changer la difficult� selon le nombre du bouton dans la liste du menu
            * F_SCORES_TABLE: Affiche la table des scores dans l'ordre d�croissant
            * F_SWITCH_MISSILES: active/d�sactive les missiles
            * F_SWITCH_DEBRIS: active/d�sactive les d�bris
            */
            void call_for(int which_function, int button_number);

        protected:

            Global_variables_container* m_GVC;

            SDL_Rect m_info_bar_size;

            Text* m_text;

            Sprite* m_screenshot;

            std::vector<Button*> m_buttons;

            bool m_done;
            bool m_parameters[MENU_PARAMETER_NUMBER];
            /*[IS_MAIN_MENU]: indique au menu si il est le menu prinipal auquel cas il supprime le GVC � la fin du programme
            * [DELETE_SCREENSHOT]: indique si il faut supprimer la screenshot
            */

    };



    //int Menu(Global_variables_container* GVC);

#endif // MENU_H_INCLUDED
