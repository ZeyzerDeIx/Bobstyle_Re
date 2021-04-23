#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"
    #include "Text.h"

    class FPS
    {
        public:

            FPS(Global_variables_container* GVC);

            void display(); //affiche les fps en bas � droite de l'�cran
            void reset(); //reset le timer et le frame save

        private:

            Global_variables_container* m_GVC;

            Text m_text; //le texte qui sert � afficher les fps

            int m_fps; //nombre de frame par seconde
            int m_timer; //temps �coul� (sert � savoir quand une seconde est pass�e)
            int m_frame_save; //nombre de frame �coul�es durant la derni�re seconde

    };

#endif // FPS_H_INCLUDED
