#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"

    class Timer
    {
        public:

            Timer(); //constructeur

            int get_elapsed_time(); //renvoit le temps écoulé depuis la derniere réinitialisation
            int get_and_restart(); //renvoit le temps écoulé depuis la derniere réinitialisation puis réinitialise le chronomètre

            void restart(); //réinitialise le chronomètre

        private:

            int m_last_time_save; //permet de sauvegarder un temps

    };

#endif // TIMER_H_INCLUDED
