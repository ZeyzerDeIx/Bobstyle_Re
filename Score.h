#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"
    #include "Text.h"

    class Score
    {
        public:

            Score(Global_variables_container* GVC);

            void display();
            void disable();

            int get_score();

        private:

            Global_variables_container* m_GVC;

            Text m_text;

            bool m_enable;

            int m_score;
            int m_frame_save;

    };

#endif // SCORE_H_INCLUDED
