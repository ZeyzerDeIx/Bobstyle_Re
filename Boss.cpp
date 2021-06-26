#include "Boss.h"

using namespace std;

Boss::Boss(Global_variables_container* GVC, Entity* target, Generator *generator, std::string image_location, int anim_numb_phase): Entity(GVC, image_location, anim_numb_phase)
{
    m_target = target;

    m_pos[Y] -= this->get_size(H)+2;

    this->set_parameter(IN_SCREEN, true);
    this->set_parameter(MOTION, true);

    m_movement[LEFT] = true;

    m_speed = 100;

    if(image_location == "sprites/DEBUG/DEBUG_BOSS.bmp")
    {
        m_weapons.push_back(new Weapon(GVC, target, generator, -120, 80));
        m_weapons.push_back(new Weapon(GVC, target, generator, 120, 80));
    }
}

Boss::~Boss(){for(int i=0 ; i<m_weapons.size() ; i++){delete m_weapons[i];}}

void Boss::manage()
{
    Entity::manage();
    for(int i=0 ; i<m_weapons.size() ; i++)
    {
        m_weapons[i]->update_pos(m_pos[X], m_pos[Y]);
        m_weapons[i]->manage();
    }
    if(m_parameters[IS_ON_BORDER])
    {
        m_movement[LEFT] = !m_movement[LEFT];
        m_movement[RIGHT] = !m_movement[RIGHT];
    }
}

void Boss::display()
{
    Entity::display();
    for(int i=0 ; i<m_weapons.size() ; i++)
    {
        m_weapons[i]->display();
    }
}
