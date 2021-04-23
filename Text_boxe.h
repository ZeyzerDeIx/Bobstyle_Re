#ifndef TEXT_BOXE_H_INCLUDED
#define TEXT_BOXE_H_INCLUDED

    #include "constants.h"
    #include "Text.h"
    #include "Menu.h"

    class Text_boxe: public Menu
    {
        public:

            Text_boxe();
            Text_boxe(Global_variables_container* GVC, std::string text_longer, int parameter = 0); //texte centré par defaut
            ~Text_boxe();

            void display();
            void click(int up_or_down = DOWN);

        private:

            Global_variables_container* m_GVC;

            std::vector<Text*> m_text_displayers;

            std::string m_text_longer;

            int m_size[2];

    };

#endif // TEXT_BOXE_H_INCLUDED
