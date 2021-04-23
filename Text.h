#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

    #include "Sprite.h"

    class Text : public Sprite
    {
        public:
            Text();
            Text(Global_variables_container* GVC, std::string text = "Missing_text", int font_size = 60, std::string font_name = "papyrus");
            ~Text();
            void change_text(std::string new_text, bool underline = false, int R = 0, int G = 0, int B = 0, int new_size = 0);
        protected:
            std::string m_text;
            std::string m_font_name;
            int m_font_size;
            TTF_Font* m_font;
    };

#endif // TEXT_H_INCLUDED
