#include "Cloud.h"

Cloud::Cloud(Global_variables_container* GVC): Entity(GVC, "sprites/decor/cloud.bmp")
{
    m_parameters[IN_SCREEN] = false;

    this->set_pos(rand() % m_GVC->screen()->w, m_GVC->screen()->h + m_sprite->get_size(H));
    this->set_movement(FLAG_UP);

    m_speed = 400;

    m_type = CLOUD;

    m_sprite->set_pos(0,0);
}
