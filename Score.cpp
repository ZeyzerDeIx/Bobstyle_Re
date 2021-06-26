#include "Score.h"

using namespace std;

Score::Score(Global_variables_container* GVC): m_text(GVC, "Score: ", 45)
{
    m_GVC = GVC;

    //on place le texte en haut à droite
    m_text.set_pos(m_GVC->screen()->w - m_text.get_size(W)/2 - 10, m_text.get_size(H)/2);

    m_enable = true;

    m_score = 0;
    m_frame_save = 0;
}

void Score::display()
{
    if(m_enable)
    {
        if(m_GVC->get_frame() - m_frame_save >= 30)
        {
            m_score += m_GVC->get_difficulty()+1;
            m_frame_save = m_GVC->get_frame();
        }

        //on actualise l'affichage
        m_text.change_text("Score: " + int_to_string(m_score), false, 175,175,175);

        //on place le texte en haut à droite
        m_text.set_pos(m_GVC->screen()->w - m_text.get_size(W)/2 - 10, m_text.get_size(H)/2);
    }
    m_text.display();
}

void Score::disable()
{
    m_enable = false;
    m_text.change_text("DISABLE", true, 175,175,175);
    m_text.set_pos(m_GVC->screen()->w - m_text.get_size(W)/2 - 10, m_text.get_size(H)/2);
}

int Score::get_score(){return m_score;}
