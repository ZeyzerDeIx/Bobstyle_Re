#ifndef HANDLER_H_INCLUDED
#define HANDLER_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"
    #include "usefull_fonctions.h"
    #include "Bobstyle.h"
    #include "Interface.h"
    #include "Generator.h"
    #include "Menu.h"
    #include "Timer.h"
    #include <map>

    class Interface;
    class Menu;

    class Handler
    {
        public:

            Handler();
            Handler(Global_variables_container* GVC, Bobstyle* bostyle, Interface* interf, Generator* generator, bool* done);
            Handler(Global_variables_container* GVC, Menu* menu, bool* done);
            Handler(Global_variables_container* GVC, std::string* text, bool* done);

            void handle(); //fonction principale pour gérer les entrés du joueur

            int wait(); //attend un evennement
            int event_validation(int event, bool keyup = false); //renvoit l'evennment reçu si il n'est pas déjà utilisé

            bool search_entry(int searched_entry); //retourne vrai si l'entrée recherchée est active
            bool search_key(int searched_key); //retourne vrai si la touche recherchée est active

        private:

            Global_variables_container* m_GVC; //pointeur vers l'écran

            SDL_Event m_event; //pour stoquer les evennements et les traiter

            std::map<int, bool> m_dictionary; //map qui sert à savoir quelle touche est enfoncée

            bool* m_done; //pointeur vers le bool qui fait continuer le jeu
            bool m_ctrl; //vaut true quand le joueur appuis sur control

            int m_mode; //sert à choisir le mode (GAME, MENU ou WRITE)

            std::string* m_text; //sert à écrire les entrés

            Bobstyle* m_bobstyle; //pointeur vers le personnage

            Interface* m_interface; //pointeur vers l'interface

            Generator* m_generator; //pointeur vers le générateur

            Menu* m_menu; //pointeur vers le menu

            Timer m_timer; //chronomètre
    };

#endif // HANDLER_H_INCLUDED
