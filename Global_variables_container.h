#ifndef GLOBAL_VARIABLES_CONTAINER_H_INCLUDED
#define GLOBAL_VARIABLES_CONTAINER_H_INCLUDED

    #include "constants.h"

    class Global_variables_container
    {
        public:
            Global_variables_container(SDL_Window* window, SDL_Surface*  screen, SDL_Renderer*  renderer);
            ~Global_variables_container();

            SDL_Window* window(); //sert � rien?
            SDL_Surface* screen(); //sert � connaitre la taille de l'�cran
            SDL_Renderer* renderer(); //sert � l'affichage

            void update_frame(); //sert � compter le nombre de frame �coul�es depuis le d�but de la partie
            void reset_frame(); //remet le compteur de frame � 0
            int get_frame(); //donne le nombre de frame �coul�es depuis le d�but de la partie

            void set_difficulty(int new_difficulty);
            int get_difficulty();

            void set_cursor_pos(int x, int y);
            int get_cursor_pos(int x_or_y);

            void set_game_parameter(int wich_parameter, bool enable);
            bool get_game_parameter(int wich_parameter);

            void set_lag(int lag);
            int get_lag();

        private:
            SDL_Window* m_window;
            SDL_Surface* m_screen;
            SDL_Renderer* m_renderer;

            int m_frame_counter; //le nombre de frame �coul�es depuis le d�but de la partie
            int m_difficulty; //la difficult�
            int m_lag; //� quel point le jeu lag
            int m_cursor_pos[2]; //la position du curseur

            bool m_parameters[P_PARAMETER_NUMBER]; //les param�tres du jeu
    };

#endif // GLOBAL_VARIABLES_CONTAINER_H_INCLUDED
