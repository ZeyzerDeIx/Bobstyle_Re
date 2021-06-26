#include "Projectile.h"

using namespace std;

Projectile::Projectile(Global_variables_container* GVC, Entity* target, int x, int y, string image_location, int anim_numb_phase):
    Entity(GVC, image_location, anim_numb_phase),
    m_vector(m_pos[X], m_pos[Y], target->get_pos(X), target->get_pos(Y))
{
    m_target = target; //la cible

    m_parameters[IN_SCREEN] = false; //pas oblig� de rester dans l�cran
    m_parameters[COLLISIONNABLE] = true; //peut �tre toucher par/toucher d'autres entit�s

    m_type = PROJECTILE; //type: missile guid�

    m_damages = 1; //les d�gats

    if(x == 0 and y == 0) //Si aucune coordonn�e n'est sp�cifi�e
    {
        int rdm(rand() % RANDOM); //une variable al�atoire qui definira de quel bord de l'�cran apparaitra le missile

        if(rdm == TOP){m_pos[X] = rand()%m_GVC->screen()->w;m_pos[Y] = -100;} //depuis le haut
        else if(rdm == BOTTOM){m_pos[X] = rand()%m_GVC->screen()->w;m_pos[Y] = m_GVC->screen()->h + 100;} //depuis le bas
        else if(rdm == LEFT){m_pos[X] = -100;m_pos[Y] = rand()%m_GVC->screen()->h;} //depuis la gauche
        else if(rdm == RIGHT){m_pos[X] = m_GVC->screen()->w + 100;m_pos[Y] = rand()%m_GVC->screen()->h;} //depuis la droite
        else{cerr << "Erreur: Nombre invalide tir� pour l'apparition d'un missile: " << rdm << endl;} //en cas de bug
    }
    else{m_pos[X] = x; m_pos[Y] = y;} //Sinon on met les coordonn�es donn�es

    m_hitbox.update(m_pos[X], m_pos[Y]); //on ajuste la hitbox selon la position tir�e
    m_sprite->set_pos(m_pos[X], m_pos[Y]); //pareil pour le sprite

    m_speed = rand() % (m_GVC->get_difficulty()+1) + 3; //on tire la vitesse de mani�re al�atoir selon la difficult�e

    m_frame_counter = m_GVC->get_frame(); //on initialise le compteur de frame

    //on initialise le vecteur
    m_vector.set_a(m_pos[X], m_pos[Y]);
    m_vector.set_b(m_target->get_pos(X), m_target->get_pos(Y));
}

void Projectile::manage()
{
    Entity::manage(); //on appel d'abord la fonction manage de la classe m�re

    if(m_vector.get_norm() != 0) //si la distance � la cible est diff�rente de 0
    { //on effectue un d�placement sur le vecteur (dans la direction de la cible) selon le compteur de frame
        m_pos[X] = m_vector.get_a(X) + (m_vector.get_x() * (m_speed*(m_GVC->get_frame() - m_frame_counter)) / m_vector.get_norm());
        m_pos[Y] = m_vector.get_a(Y) + (m_vector.get_y() * (m_speed*(m_GVC->get_frame() - m_frame_counter)) / m_vector.get_norm());
    }

    if(m_vector.get_b(X) != m_target->get_pos(X) or m_vector.get_b(Y) != m_target->get_pos(Y)) //si la cible bouge
    {
        m_frame_counter = m_GVC->get_frame(); //on actualise le compteur de frame

        //on actualise le vecteur
        m_vector.set_a(m_pos[X], m_pos[Y]);
        m_vector.set_b(m_target->get_pos(X), m_target->get_pos(Y));
    }

    this->spin(-m_vector.get_angle()-m_angle); //on fait tourner le missile selon l'orientation de son vecteur
}

void Projectile::display()
{
    Entity::display(); //fonction display de la classe m�re

    if(m_parameters[DEBUG_MODE])
    {
        m_vector.show_debug_line(m_GVC); //en cas de debug mode on affiche le vecteur
    }
}
