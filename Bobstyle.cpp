#include "Bobstyle.h"

using namespace std;

Bobstyle::Bobstyle(Global_variables_container* GVC): Entity(GVC, "sprites/bobstyle/Bob_Style.bmp"), m_cursor(m_pos[X],m_pos[Y],1,1)
{
    m_speed_lines = new Animated_sprite(m_GVC, "sprites/bobstyle/speed_lines.bmp", 32);
    m_bobstyle_thruster = new Animated_sprite(m_GVC, "sprites/bobstyle/bob_style_thruster.bmp", BOBSTYLE_TRUSTER_PHASES);
    m_tp_line = new Sprite(m_GVC, "sprites/bobstyle/tp_line.bmp");

    m_sprite->spin(180);

    m_parameters[COLLISIONNABLE] = true;

    m_tp_vector[PREVIOUS].set_a(m_pos[X], m_pos[Y]);
    m_tp_vector[PREVIOUS].set_b(m_pos[X], m_pos[Y] - m_tp_line->get_size(H)/2);
    m_tp_vector[CURRENT] = m_tp_vector[PREVIOUS];

    m_is_dashing = false;

    m_frame_counter = 0;
    m_hp = 20;
    m_dash_timer = SDL_GetTicks();
    m_cooldown = 400;
    m_speed = 150;
}
Bobstyle::~Bobstyle()
{
    delete m_speed_lines;
    delete m_bobstyle_thruster;
    delete m_tp_line;
}

int Bobstyle::get_hp()
{
    return m_hp;
}

void Bobstyle::manage()
{
    //d'abord on appel la fonction manage basique de Entity
    Entity::manage();

    //si bobstyle dash
    if(m_is_dashing)
    {
        //on actualise tout
        m_bobstyle_thruster->set_pos(m_tp_vector[CURRENT].get_a(X) + m_tp_vector[CURRENT].get_x()*m_frame_counter/BOBSTYLE_TRUSTER_PHASES,
                                     m_tp_vector[CURRENT].get_a(Y) + m_tp_vector[CURRENT].get_y()*m_frame_counter/BOBSTYLE_TRUSTER_PHASES);

        m_pos[X] = m_bobstyle_thruster->get_pos(X);
        m_pos[Y] = m_bobstyle_thruster->get_pos(Y);
        m_sprite->set_pos(m_pos[X], m_pos[Y]);

        //on force bobstyle à rester dans l'écran
        this->stay_in_screen(this->out_of_screen());

        //si le dash est fini
        if(m_frame_counter >= BOBSTYLE_TRUSTER_PHASES)
        {
            m_frame_counter = 0;
            this->dash(END);
        }

        //on incrémente le compteur pour savoir quand le dash sera fini
        m_frame_counter ++;
    }

    //on fait en sorte que la ligne de tp suive bobstyle
    m_tp_line->set_pos(m_pos[X], m_pos[Y]);

    //pareil pour les lignes de vitesse
    m_speed_lines->set_pos(m_pos[X], m_pos[Y] - m_sprite->get_size(H)/2 - m_speed_lines->get_size(H)/2);

    //on met à jour la ligne de tp (angle et position)
    this->update_tp_line();
}

void Bobstyle::display()
{
    if(!m_parameters[DEBUG_MODE] and !m_is_dashing)
    {
        m_tp_line->display();
    }

    if(!m_is_dashing)
    {
        Entity::display();

        m_speed_lines->display();
    }
    else
    {
        m_bobstyle_thruster->display();
    }

    if(m_parameters[DEBUG_MODE])
    {
        m_cursor.show_debug_line(m_GVC);
        m_tp_vector[CURRENT].show_debug_line(m_GVC);
    }
}

void Bobstyle::update_tp_line()
{
    m_cursor.set_a(m_pos[X], m_pos[Y]);
    m_cursor.set_b(m_GVC->get_cursor_pos(X), m_GVC->get_cursor_pos(Y));

    if(!m_is_dashing)
    {
        m_tp_vector[CURRENT] = m_tp_vector[PREVIOUS];
        m_tp_vector[CURRENT].spin(m_cursor.get_angle());
        m_tp_vector[CURRENT].shift(m_pos[X] - m_tp_vector[CURRENT].get_a(X), m_pos[Y] - m_tp_vector[CURRENT].get_a(Y));


        m_tp_line->reset_angle();
        m_tp_line->spin(-m_cursor.get_angle());
    }
}

void Bobstyle::dash(int instruction)
{
    if(instruction == BEGIN)
    {
        if(!m_is_dashing and SDL_GetTicks() - m_dash_timer > m_cooldown)
        {
            m_is_dashing = true;

            m_frame_counter = 0;

            m_parameters[COLLISIONNABLE] = false;

            m_bobstyle_thruster->spin(360 - m_tp_vector[CURRENT].get_angle());

            m_bobstyle_thruster->set_pos(m_tp_vector[CURRENT].get_a(X), m_tp_vector[CURRENT].get_a(Y));
        }
        else if(!m_is_dashing){m_dash_timer = SDL_GetTicks();}
    }
    else
    {
        m_is_dashing = false;

        m_frame_counter = 0;

        m_parameters[COLLISIONNABLE] = true;

        m_bobstyle_thruster->reset_angle();

        m_pos[X] = m_bobstyle_thruster->get_pos(X);
        m_pos[Y] = m_bobstyle_thruster->get_pos(Y);
    }
}

void Bobstyle::stay_in_screen(Uint32 borders)
{ //recale l'entité dans l'écran selon où elle deborde
    if((borders & FLAG_UP) == FLAG_UP)
    {
        m_pos[Y] = TOP_BORDER_HIGHT + m_sprite->get_size(H)/2;
    }
    else if((borders & FLAG_DOWN) == FLAG_DOWN)
    {
        m_pos[Y] = m_GVC->screen()->h - m_sprite->get_size(H)/2;
    }
    if((borders & FLAG_LEFT) == FLAG_LEFT)
    {
        m_pos[X] = m_sprite->get_size(W)/2;
    }
    else if((borders & FLAG_RIGHT) == FLAG_RIGHT)
    {
        m_pos[X] = m_GVC->screen()->w - m_sprite->get_size(W)/2;
    }
    //on actualise la position des sprite
    m_sprite->set_pos(m_pos[X], m_pos[Y]);
    m_bobstyle_thruster->set_pos(m_pos[X], m_pos[Y]);
}

void Bobstyle::lose_hp(int lost_hp)
{
    m_hp -= lost_hp;
    if(m_hp <= 0)
    {
        m_parameters[ALIVE] = false;
    }
}

void Bobstyle::reset_movements()
{
    for(int i = 0 ; i<4 ; i++)
    {
        m_movement[i] = false;
    }
}
