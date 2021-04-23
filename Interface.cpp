#include "Interface.h"

using namespace std;

Interface::Interface(Global_variables_container* GVC, Bobstyle* bobstyle, bool* done): m_fps(GVC), m_score(GVC)
{
    m_GVC = GVC;

    m_bobstyle = bobstyle;

    m_done = done;

    //la barre est positionnée en haut à gauche et prend toute la largeur de l'écran
    m_info_bar_size.x = 0;
    m_info_bar_size.y = 0;
    m_info_bar_size.w = m_GVC->screen()->w;
    m_info_bar_size.h = TOP_BORDER_HIGHT;

    //on charge les 4 coeurs de vie
    for(int i = 0 ; i<4 ; i++)
    {
        m_life[i] = new Animated_sprite(m_GVC, "sprites/bobstyle/coeur_de_vie.bmp", 5); //on les créé
        m_life[i]->set_pos(m_info_bar_size.w/20 + (m_life[i]->get_size(W) + 1)*(3-i), m_info_bar_size.h/2); //on les place
        m_life[i]->set_animation(false); //on annule leur animation automatique
    }

    m_text = new Text(m_GVC, "BOBSTYLE::RE", 50); //le titre du jeu écrit en haut au milieu pendant la partie
    m_text->change_text("SAME", true, 100); //souligné + rouge
    m_text->set_pos(m_GVC->screen()->w/2, TOP_BORDER_HIGHT/2);
}
Interface::~Interface()
{
    for(int i = 0 ; i<4 ; i++){delete m_life[i];}
    delete m_text;
}

void Interface::display()
{
    SDL_SetRenderDrawColor(m_GVC->renderer(),50,50,50,0); //on choisit la couleur à utiliser pour la barre d'info
    SDL_RenderFillRect(m_GVC->renderer(), &m_info_bar_size); //afficher la barre d'info

    //ici on gère l'affichage des pv
    for(int i = 0 ; i<4 ; i++) //pour chaque coeur (en partant de la droite)
    {
        if(m_bobstyle->get_hp() <= 5*(3-i)){(*m_life[i])[4]->display();} //on verifie qu'il n'est pas supposé être vide
        else if(m_bobstyle->get_hp() >= 5*(4-i)){(*m_life[i])[0]->display();} //ou plein
        else{(*m_life[i])[4 - (m_bobstyle->get_hp()- 5*(3-i))]->display();} //sinon on le met au bon niveau
    }

    m_text->display(); //on affiche le titre du jeu

    m_fps.display(); //on affiche les fps en bas à droite de l'écran

    m_score.display();
}

void Interface::pause() //à revoir!
{
    //permet d'éviter des bugs de direction à la sortie de la pause
    m_bobstyle->reset_movements();

    //on créer un menu avec un bouton qui garde une screenshot de la partie en cours en arrière plan
    Menu pause_menu(m_GVC, 1, 1, screenshot(m_GVC, 150));
    //Le bouton 1 permet de reprendre
    pause_menu.set_button(1, F_QUIT, "Reprendre");
    //le titre du menu est "Pause"
    pause_menu.set_caption("Pause");
    //on lance le menu
    pause_menu.start();

    //une fois la pause terminée on reset les compteurs des fps pour ne pas qu'ils soient influencés par la pause
    m_fps.reset();
}

int Interface::get_score(){return m_score.get_score();}
