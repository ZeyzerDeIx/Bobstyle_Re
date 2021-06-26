#include "Generator.h"

using namespace std;

Generator::Generator(Global_variables_container* GVC, Entity* bobstyle)
{
    m_GVC = GVC;

    m_bobstyle = bobstyle;

    m_debug_mode = false;
    m_auto_gen = false;

    for(int i = 0 ; i<MAX_ENTITY_NUMBER+1 ; i++){m_last_frame[i] = 0;}
}

Generator::~Generator()
{
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        delete *it;
    }
}

void Generator::generate_entities(int type, int x, int y, Entity *target, int number)
{
    if(target == NULL){target = m_bobstyle;}
    for(int i = 0 ; i<number ; i++)
    {
        switch(type)
        {
            case DEBRIS:
                m_entities.push_back(new Debris(m_GVC, debris_rand()));
                break;
            case CLOUD:
                m_entities.push_back(new Cloud(m_GVC));
                break;
            case HOMING_MISSILE:
                m_entities.push_back(new Homing_missile(m_GVC, target, x, y));
                break;
            case PROJECTILE:
                m_entities.push_back(new Projectile(m_GVC, target, x, y));
                break;
        }
    }

    if(m_debug_mode)
    { //on met l'entité créée en debug mode si il est actif
        list<Entity*>::iterator it = m_entities.end();
        it--;
        (*it)->set_parameter(DEBUG_MODE, true);
    }
}

void Generator::set_auto_generation(bool enable)
{
    m_auto_gen = enable;
}

void Generator::clear_dead_entity()
{
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        if(!(*it)->get_parameter(ALIVE))
        {
            delete *it;
            m_entities.erase(it);
            this->clear_dead_entity();
            break;
        }
    }
}

void Generator::manage()
{
    this->clear_dead_entity();

    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        (*it)->manage();
    }

    if(m_auto_gen)
    {
        if(m_GVC->get_game_parameter(P_DEBRIS_ON))
        {
            if(m_GVC->get_frame() - m_last_frame[DEBRIS] >= ((UNFAIR - m_GVC->get_difficulty())*(UNFAIR - m_GVC->get_difficulty())))
            {
                this->generate_entities(DEBRIS);
                m_last_frame[DEBRIS] = m_GVC->get_frame();
            }
        }
        if(m_GVC->get_game_parameter(P_MISSILES_ON))
        {
            if(m_GVC->get_frame() - m_last_frame[HOMING_MISSILE] >= 170 - 40*m_GVC->get_difficulty())
            {
                this->generate_entities(HOMING_MISSILE);
                m_last_frame[HOMING_MISSILE] = m_GVC->get_frame();
            }
        }
    }
    if(m_clouds_enable and m_GVC->get_frame() - m_last_frame[CLOUD] >= 20)
    {
        this->generate_entities(CLOUD);
        m_last_frame[CLOUD] = m_GVC->get_frame();
    }

    if(m_GVC->get_frame() - m_last_frame[MAX_ENTITY_NUMBER] >= m_GVC->get_lag()+1) //l'interval s'adapte aux lags
    {
        for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) //double boucle qui gère les collisions entre les missiles
        {
            for(list<Entity*>::iterator it2 = m_entities.begin(); it2 != m_entities.end(); ++it2)
            {
                if((*it)->collision(*it2) and it != it2)
                {
                    (*it)->set_parameter(ALIVE, false);
                    (*it2)->set_parameter(ALIVE, false);
                }
            }
        }

        m_last_frame[MAX_ENTITY_NUMBER] = m_GVC->get_frame();
    }
}

void Generator::display()
{
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        (*it)->display();
    }
}

void Generator::manage_and_display()
{
    this->manage();
    this->display();
}

void Generator::set_debug_mode(bool enable)
{
    m_debug_mode = enable;

    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        (*it)->set_parameter(DEBUG_MODE, enable);
    }
}

void Generator::set_clouds(bool enable){m_clouds_enable = enable;}

void Generator::manage_collisions(Entity* enty)
{
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        if(enty != 0)
        {
            if((*it)->collision(enty))
            {
                enty->lose_hp((*it)->get_damage());
                (*it)->set_parameter(ALIVE, false);
            }
        }
    }
}

bool Generator::get_debug_mode()
{
    return m_debug_mode;
}

int Generator::get_type_occurences(int type)
{
    int counter(0);
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        if((*it)->get_type() == type){counter++;}
    }

    return counter;
}
