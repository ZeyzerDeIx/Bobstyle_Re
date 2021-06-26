#include "Weapon.h"

using namespace std;

Weapon::Weapon(Global_variables_container *GVC,
               Entity *target,
               Generator *generator,
               int relative_x,
               int relative_y,
               string image_location,
               int anim_numb_phase)
{
    m_GVC = GVC;

    m_generator = generator;

    m_target = target;

    m_relative_pos[X] = relative_x;
    m_relative_pos[Y] = relative_y;

    m_appearence = new Entity(GVC, image_location, anim_numb_phase);
    m_appearence->set_parameter(COLLISIONNABLE, true);

    //on initialise le vecteur
    m_vector.set_a(m_appearence->get_pos(X), m_appearence->get_pos(Y));
    m_vector.set_b(m_target->get_pos(X), m_target->get_pos(Y));

    m_debug_mode = false;
}

Weapon::~Weapon(){delete m_appearence;}

void Weapon::manage()
{
    m_appearence->manage();
    this->manage_collisions(m_target);
    m_vector.set_a(m_appearence->get_pos(X), m_appearence->get_pos(Y));
    m_vector.set_b(m_target->get_pos(X), m_target->get_pos(Y));
    m_appearence->spin(-m_vector.get_angle()-m_appearence->get_angle());
}

void Weapon::display()
{
    m_appearence->display();

    if(m_debug_mode)
    {
        m_vector.show_debug_line(m_GVC);
    }
}

void Weapon::manage_and_display(){this->manage();this->display();}

void Weapon::manage_collisions(Entity *ent)
{
    if(m_appearence->collision(ent))
    {
        ent->lose_hp(5); //la cible perd des pv
        int vecnorm(m_vector.get_norm() + 1*(m_vector.get_norm()==0)); //evite la division par zero
        //on expulse la cible dans la direction d'où elle arrive
        ent->set_pos(ent->get_pos(X) + m_vector.get_x()+(vecnorm==1) * (m_appearence->get_size(H) / vecnorm),
                     ent->get_pos(Y) + m_vector.get_y()+(vecnorm==1) * (m_appearence->get_size(H) / vecnorm));
    }
}

void Weapon::set_debug_mode(bool enable){m_appearence->set_parameter(DEBUG_MODE, enable);m_debug_mode = enable;}

void Weapon::update_pos(int x, int y)
{
    m_appearence->set_pos(x+m_relative_pos[X], y+m_relative_pos[Y]);
}

void Weapon::fire()
{
    if(m_vector.get_norm() != 0)
    {
        m_generator->generate_entities(PROJECTILE,
            m_appearence->get_pos(X) + m_vector.get_x() * (m_appearence->get_size(H) / m_vector.get_norm()),
            m_appearence->get_pos(Y) + m_vector.get_y() * (m_appearence->get_size(H) / m_vector.get_norm()),
            m_target);
    }
}
