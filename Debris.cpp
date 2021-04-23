#include "Debris.h"

using namespace std;

Debris::Debris(Global_variables_container* GVC, int dimension): Entity(GVC, "sprites/hostile entity/debris/"+int_to_string(dimension)+".bmp")
{
    m_dimension = dimension;
    m_sprite->set_anim_speed(7);

    m_parameters[IN_SCREEN] = false;
    m_parameters[COLLISIONNABLE] = true;

    this->set_pos(rand() % m_GVC->screen()->w, 0);
    this->set_movement(FLAG_DOWN);

    m_speed = 200/(m_dimension+3) * (m_GVC->get_difficulty()+2);

    m_type = DEBRIS;

    m_damages = dimension+1;

    m_sprite->set_pos(0,0);
}
