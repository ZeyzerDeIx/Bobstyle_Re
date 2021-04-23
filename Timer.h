#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"

    class Timer
    {
        public:

            Timer();

            int get_elapsed_time();
            int get_and_restart();

            void restart();

        private:

            int m_last_time_save;

    };

#endif // TIMER_H_INCLUDED
