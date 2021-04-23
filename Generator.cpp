#include "Generator.h"

using namespace std;

Generator::Generator(Global_variables_container* GVC)
{
    m_GVC = GVC;

    m_debug_mode = false;
    m_auto_gen = false;

    m_frame_counter = 0;

    for(int i = 0 ; i<MAX_ENTITY_NUMBER ; i++){m_last_frame[i] = 0;}
}

Generator::~Generator()
{
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        delete *it;
    }
}

void Generator::generate_entities(int type, int number)
{
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
        }
    }

    if(m_debug_mode)
    {
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

    m_frame_counter += 1;

    if(m_auto_gen)
    {
        if(m_frame_counter - m_last_frame[DEBRIS] >= ((UNFAIR - m_GVC->get_difficulty())*(UNFAIR - m_GVC->get_difficulty()))/2)
        {
            this->generate_entities(DEBRIS);
            m_last_frame[DEBRIS] = m_frame_counter;
        }
    }
    if(m_frame_counter - m_last_frame[CLOUD] >= 20)
    {
        this->generate_entities(CLOUD);
        m_last_frame[CLOUD] = m_frame_counter;
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

void Generator::manage_collisions(Bobstyle* bobstl)
{
    for(list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        if(bobstl != nullptr)
        {
            if(bobstl->collision((*it)))
            {
                bobstl->lose_hp((*it)->get_damage());
                (*it)->set_parameter(ALIVE, false);
            }
        }
    }
}

bool Generator::get_debug_mode()
{
    return m_debug_mode;
}
