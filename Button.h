#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"
    #include "Text.h"
    #include <vector>


    class Button
    {
        public:

            Button(Global_variables_container* GVC, std::string text = "O");
            ~Button();

            void display();
            void set_pos(int x, int y);
            void update();
            void click(int up_or_down = DOWN);
            void rework(int new_function, std::string new_text = "SAME", int new_text_size = 0);

            bool under_cursor();
            bool is_clicked();

            int get_function();

        private:

            Global_variables_container* m_GVC;

            Animated_sprite* m_sprite;

            Text* m_text;

            int m_function;

            bool m_is_clicked;
    };

#endif // BUTTON_H_INCLUDED
