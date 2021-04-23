#include "Hitbox.h"

using namespace std;

Hitbox::Hitbox(){}

Hitbox::Hitbox(int center_x, int center_y, int w, int h)
{
    m_w = w;
    m_h = h;

    //Les vecteurs fixes et changeants sont créé de manières identiques à la base
    for(int i = 0 ; i<2 ; i++)
    {
        //Le prime vector va du centre de la hitbox vers à son angle supérieur gauche
        m_vectors[PRIME][i] = Vector(center_x, center_y, center_x-(w/2), center_y-(h/2));

        //Le top vector va de l'angle supérieur gauche à l'angle supérieur droit
        m_vectors[TOP][i] = Vector(m_vectors[PRIME][i].get_b(X), m_vectors[PRIME][i].get_b(Y), m_vectors[PRIME][i].get_b(X)+w, m_vectors[PRIME][i].get_b(Y));

        //Le right vector va de l'angle supérieur droit à l'angle inférieur droit
        m_vectors[RIGHT][i] = Vector(m_vectors[TOP][i].get_b(X), m_vectors[TOP][i].get_b(Y), m_vectors[TOP][i].get_b(X), m_vectors[TOP][i].get_b(Y)+h);

        //Le left vector va de l'angle supérieur gauche à l'angle inférieur gauche
        m_vectors[LEFT][i] = Vector(m_vectors[PRIME][i].get_b(X), m_vectors[PRIME][i].get_b(Y), m_vectors[PRIME][i].get_b(X), m_vectors[PRIME][i].get_b(Y)+h);

        //Le bottom vector va de l'angle inférieur gauche à l'angle inférieur droit
        m_vectors[BOTTOM][i] = Vector(m_vectors[LEFT][i].get_b(X), m_vectors[LEFT][i].get_b(Y), m_vectors[LEFT][i].get_b(X)+w, m_vectors[LEFT][i].get_b(Y));
    }

    //par defaut l'angle vaut 0
    m_angle = 0;
}

bool Hitbox::collision(Hitbox *other)
{
    for(int i=0 ; i<4 ; i++)
    {
        for(int j=0 ; j<4 ; j++)
        {
            if(m_vectors[i][CURRENT].intersect(other->get_vector(j)))
            {
                return true;
            }
        }
    }
    return false;
}

Vector* Hitbox::get_vector(int wich)
{
    return &m_vectors[wich][CURRENT];
}

void Hitbox::show(Global_variables_container* GVC)
{
    //on fait apparaitre les 4 bordures de la hitbox
    for(int i=0 ; i<4 ; i++)
    {
        m_vectors[i][CURRENT].show_debug_line(GVC);
    }
}

void Hitbox::update(int new_x, int new_y)
{
    //Les vecteurs fixes et changeants sont créé de manières identiques à la base
    for(int i = 0 ; i<2 ; i++)
    {
        //Le prime vector va du centre de la hitbox vers à son angle supérieur gauche
        m_vectors[PRIME][i] = Vector(new_x, new_y, new_x-(m_w/2), new_y-(m_h/2));

        //Le top vector va de l'angle supérieur gauche à l'angle supérieur droit
        m_vectors[TOP][i] = Vector(m_vectors[PRIME][i].get_b(X), m_vectors[PRIME][i].get_b(Y), m_vectors[PRIME][i].get_b(X)+m_w, m_vectors[PRIME][i].get_b(Y));

        //Le right vector va de l'angle supérieur droit à l'angle inférieur droit
        m_vectors[RIGHT][i] = Vector(m_vectors[TOP][i].get_b(X), m_vectors[TOP][i].get_b(Y), m_vectors[TOP][i].get_b(X), m_vectors[TOP][i].get_b(Y)+m_h);

        //Le left vector va de l'angle supérieur gauche à l'angle inférieur gauche
        m_vectors[LEFT][i] = Vector(m_vectors[PRIME][i].get_b(X), m_vectors[PRIME][i].get_b(Y), m_vectors[PRIME][i].get_b(X), m_vectors[PRIME][i].get_b(Y)+m_h);

        //Le bottom vector va de l'angle inférieur gauche à l'angle inférieur droit
        m_vectors[BOTTOM][i] = Vector(m_vectors[LEFT][i].get_b(X), m_vectors[LEFT][i].get_b(Y), m_vectors[LEFT][i].get_b(X)+m_w, m_vectors[LEFT][i].get_b(Y));
    }
    this->spin(0);
}

void Hitbox::spin(int angle)
{
    //on actualise l'angle dans le bon sens
    m_angle -= angle;
    //on surveille qu'il ne depasse pas inutilement -360°
    if(m_angle <= 360)
    {
        m_angle += 360;
    }

    //on reset les vecteur
    for(int i=0 ; i<5 ; i++)
    {
        m_vectors[i][CURRENT] = m_vectors[i][PREVIOUS];
    }
    //on fait tourner le premier vecteur et on reconstruit toute la hitbox en suivant le même schema que dans le constructeur
    {
    m_vectors[PRIME][CURRENT].spin(m_angle);

    m_vectors[TOP][CURRENT].shift(m_vectors[PRIME][CURRENT].get_b(X) - m_vectors[PRIME][PREVIOUS].get_b(X),
                                  m_vectors[PRIME][CURRENT].get_b(Y) - m_vectors[PRIME][PREVIOUS].get_b(Y));
    m_vectors[TOP][CURRENT].spin(m_angle);

    m_vectors[RIGHT][CURRENT].shift(m_vectors[TOP][CURRENT].get_b(X) - m_vectors[TOP][PREVIOUS].get_b(X),
                                  m_vectors[TOP][CURRENT].get_b(Y) - m_vectors[TOP][PREVIOUS].get_b(Y));
    m_vectors[RIGHT][CURRENT].spin(m_angle);

    m_vectors[LEFT][CURRENT].shift(m_vectors[PRIME][CURRENT].get_b(X) - m_vectors[PRIME][PREVIOUS].get_b(X),
                                  m_vectors[PRIME][CURRENT].get_b(Y) - m_vectors[PRIME][PREVIOUS].get_b(Y));
    m_vectors[LEFT][CURRENT].spin(m_angle);

    m_vectors[BOTTOM][CURRENT].shift(m_vectors[LEFT][CURRENT].get_b(X) - m_vectors[LEFT][PREVIOUS].get_b(X),
                                  m_vectors[LEFT][CURRENT].get_b(Y) - m_vectors[LEFT][PREVIOUS].get_b(Y));
    m_vectors[BOTTOM][CURRENT].spin(m_angle);
    }
}





