#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

    #include "constants.h"
    #include "Text.h"
    #include "Handler.h"
    #include "FPS.h"
    #include "Score.h"

    class Interface
    {
        public:

            Interface(Global_variables_container* GVC, Bobstyle* bobstyle, bool* done);
            ~Interface();

            void display(); //affiche l'interface
            void pause(); //arrête le jeu et affiche le menu de pause

            int get_score(); //retourne le score

        private:

            Global_variables_container* m_GVC; //le gvc comme partout dans ce code

            Bobstyle* m_bobstyle; //un pointeur vers bobstyle pour avoir ses infos

            bool* m_done; //un pointeur pour terminer le jeu si besoin

            SDL_Rect m_info_bar_size; //contient la taille du bandeau gris qui permet d'afficher l'interface par dessus

            Animated_sprite* m_life[4]; //les coeurs représentants les pv de bobstyle

            Text* m_text; //sert à afficher le nom du jeu

            FPS m_fps; //sert à afficher les fps

            Score m_score; //sert à afficher le score
    };

#endif // INTERFACE_H_INCLUDED
