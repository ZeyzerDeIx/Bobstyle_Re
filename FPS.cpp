#include "FPS.h"

using namespace std;

FPS::FPS(Global_variables_container* GVC): m_text(GVC, "0 FPS", 30, "comic") //petite écriture en comic pour être bien lisible
{
    m_GVC = GVC;

    //on place le texte en bas à droite
    m_text.set_pos(m_GVC->screen()->w - m_text.get_size(W)/2,
                   m_GVC->screen()->h - m_text.get_size(H)/2);

    m_timer = 0;
    m_frame_save = m_GVC->get_frame();
}

void FPS::display()
{
    if(SDL_GetTicks() - m_timer >= 1000) //si une seconde est passée
    {
        m_fps = m_GVC->get_frame() - m_frame_save; //on actualise les fps
        this->reset(); //et on reset les compteurs
    }

    m_GVC->set_lag(60 - m_fps);

    //on actualise l'affichage
    m_text.change_text(int_to_string(m_fps) + " FPS");

    //on actualise aussi la position de l'affichage
    m_text.set_pos(m_GVC->screen()->w - m_text.get_size(W)/2,
                   m_GVC->screen()->h - m_text.get_size(H)/2);

    //et on affiche
    m_text.display();
}

void FPS::reset()
{
    m_timer = SDL_GetTicks(); //on actualise le timer
    m_frame_save = m_GVC->get_frame(); //et le compteur de frame
}
