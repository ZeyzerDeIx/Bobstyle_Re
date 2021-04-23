#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

    #include "constants.h"
    #include "Game.h"
    #include "Button.h"

    class Menu
    {
        public:

            Menu(Global_variables_container* GVC, int button_number = 0, int column_number = 1, Sprite* screenshot = nullptr);
            ~Menu();

            int start(); //lance le menu

            virtual void display(); //affiche le contenu du menu
            virtual void click(int up_or_down = DOWN); //informe les bouton que le joueur a cliqué
            //permet de définir un bouton, son utilité et son texte
            void set_button(int wich_button, int wich_function = F_QUIT, std::string new_text = "SAME");
            void set_caption(std::string new_text); //permet de changer le titre du menu

            /*Permet aux boutons d'appeler un fonction définie parmis les valeurs suivantes:
            * F_QUIT: Met fin au menu, le quitte
            * F_GAME: Lance une partie
            * F_OPTIONS: Créer un menu "options"
            * F_DIFFICULTY_CHOICE: Créer un menu de selection de difficulté
            * F_SET_DIFFICULTY: Permet de changer la difficulté selon le nombre du bouton dans la liste du menu
            * F_SCORES_TABLE: Affiche la table des scores dans l'ordre décroissant
            */
            void call_for(int wich_function, int button_number);

        protected:

            Global_variables_container* m_GVC;

            SDL_Rect m_info_bar_size;

            Text* m_text;

            Sprite* m_screenshot;

            std::vector<Button*> m_buttons;

            bool m_done;
            bool m_is_main_menu;

    };



    //int Menu(Global_variables_container* GVC);

#endif // MENU_H_INCLUDED
