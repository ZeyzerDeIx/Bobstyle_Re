#include "Text.h"

using namespace std;

Text::Text(){}

Text::Text(Global_variables_container* GVC, string text, int font_size, string font_name) : Sprite(GVC)
{
    m_text = text;

    m_font_name = "sprites/fonts/";
    m_font_name += font_name;
    m_font_name += ".ttf";
    m_font_size = font_size;
    m_font = TTF_OpenFont(m_font_name.c_str(), m_font_size);
    if(!m_font) {
    cout << "TTF_OpenFont: " << TTF_GetError();
    // récuperrer l'erreur
    }

    m_original_image = TTF_RenderText_Solid(m_font, text.c_str(), {175,175,175});
    m_image = SDL_CreateTextureFromSurface(m_GVC->renderer(), m_original_image);
}

Text::~Text()
{
    TTF_CloseFont(m_font);
}


void Text::change_text(string new_text, bool underline, int R, int G, int B, int new_size)
{
    SDL_DestroyTexture(m_image);
    SDL_FreeSurface(m_original_image);

    if(new_text == "SAME" or new_text == ""){new_text = m_text;}
    m_text = new_text;

    if(new_size == 0){new_size = m_font_size;}
    else
    {
        TTF_CloseFont(m_font);
        m_font = TTF_OpenFont(m_font_name.c_str(), new_size);
    }
    m_font_size = new_size;

    if(underline){TTF_SetFontStyle(m_font, TTF_STYLE_UNDERLINE);}
    else{TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);}

    m_original_image = TTF_RenderText_Solid(m_font, new_text.c_str(), {R,G,B});
    m_image = SDL_CreateTextureFromSurface(m_GVC->renderer(), m_original_image);
}
