#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"

    class Timer
    {
        public:

            Timer(); //constructeur

            int get_elapsed_time(); //renvoit le temps �coul� depuis la derniere r�initialisation
            int get_and_restart(); //renvoit le temps �coul� depuis la derniere r�initialisation puis r�initialise le chronom�tre

            void restart(); //r�initialise le chronom�tre

        private:

            int m_last_time_save; //permet de sauvegarder un temps

    };

#endif // TIMER_H_INCLUDED
