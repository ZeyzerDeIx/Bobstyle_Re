#include "Button.h"

using namespace std;

Button::Button(Global_variables_container* GVC, string text)
{
    m_GVC = GVC;

    m_sprite = new Animated_sprite(GVC, "sprites/interface/button.bmp", 2);
    m_text = new Text(GVC, text, 53 - text.size());

    m_sprite->set_animation(false);

    m_function = F_QUIT;

    m_is_clicked = false;
}

Button::~Button()
{
    delete m_sprite;
    delete m_text;
}

void Button::display()
{ //on affiche le sprite puis le texte
    this->update();
    m_sprite->display();
    m_text->display();
}

void Button::set_pos(int x, int y)
{ //change la position du bouton
    m_sprite->set_pos(x, y);
    m_text->set_pos(x, y);
}

void Button::update()
{
    if(this->under_cursor())
    { //si le curseur est sur le bouton
        m_text->change_text("SAME", true); //on souligne son texte
    }
    else
    { //si le curseur est hors du bouton
        m_text->change_text("SAME", false); //le texte n'est plus souligné
        if(m_is_clicked)
        { //et si le bouton était en état de click, il ne l'est plus
            m_is_clicked = false;
            m_sprite->reset_animation();
        }
    }
}

void Button::click(int up_or_down)
{
    if(this->under_cursor())
    { //si le bouton est sous le curseur lors du click
        m_is_clicked = (up_or_down == DOWN); //vrai si le click est enffoncé
        m_sprite->skip_phase(1); //on inverse son état visuel (comme il n'y a que 2 images possibles elles s'inversent d'elles même)
    }
    if(up_or_down == UP){m_sprite->reset_animation();}
}

void Button::rework(int new_function, string new_text, int new_text_size)
{
    m_function = new_function;
    m_text->change_text(new_text, false, 0, 0, 0, new_text_size);
}

bool Button::under_cursor()
{ //renvoit vrai si le curseur est sur le bouton
    return (m_GVC->get_cursor_pos(X) < m_sprite->get_border(RIGHT) and
            m_GVC->get_cursor_pos(X) > m_sprite->get_border(LEFT) and
            m_GVC->get_cursor_pos(Y) < m_sprite->get_border(BOTTOM) and
            m_GVC->get_cursor_pos(Y) > m_sprite->get_border(TOP));
}

bool Button::is_clicked()
{
    return m_is_clicked;
}

int Button::get_function()
{
    return m_function;
}
