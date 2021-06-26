#include "Entity.h"

using namespace std;

Entity::Entity(Global_variables_container* GVC, string image_location ,int anim_numb_phase)
{
    m_GVC = GVC;
    m_sprite = new Animated_sprite(m_GVC, image_location, anim_numb_phase); //on charge le sprite

    m_hitbox = Hitbox(m_sprite->get_pos(X),
                      m_sprite->get_pos(Y),
                      m_sprite->get_border(RIGHT)-m_sprite->get_border(LEFT),
                      m_sprite->get_border(BOTTOM)-m_sprite->get_border(TOP));

    //on cale la position sur les cooredonnés du centre du sprite
    m_pos[X] = m_sprite->get_pos(X);
    m_pos[Y] = m_sprite->get_pos(Y);

    //aucune direction par defaut
    for(int i = 0; i<4 ; i++)
    {
        m_movement[i] = false;
    }

    m_speed = 200; //vitesse par defaut en pixel/second

    //l'angle par defaut est de 0
    m_angle = 0;

    //on établit les paramètres par defaut
    m_parameters[DEBUG_MODE] = false;
    m_parameters[ALIVE] = true;
    m_parameters[IN_SCREEN] = true;
    m_parameters[MOTION] = true;
    m_parameters[COLLISIONNABLE] = false;
    m_parameters[ANIMATED] = true;
    m_parameters[BOOMERANG] = false;
    m_parameters[IS_ON_BORDER] = false;

    //on fixe les dommages pas defaut à 0
    m_damages = 0;

    //on defini le type de l'entité
    m_type = ENTITY;

    m_hp = 1;
}

Entity::~Entity()
{
    delete m_sprite;
}



void Entity::set_movement(Uint32 flag_directions)
{
    //on reçoit l'instruction (vers le haut, bas ,gauche ou droite)
    //on inverse le bool qui correspond pour indiquer vers ou va l'entité
    if((flag_directions & FLAG_UP) == FLAG_UP)
    {
        m_movement[UP] = !m_movement[UP];
    }
    else if((flag_directions & FLAG_DOWN) == FLAG_DOWN)
    {
        m_movement[DOWN] = !m_movement[DOWN];
    }
    if((flag_directions & FLAG_RIGHT) == FLAG_RIGHT)
    {
        m_movement[RIGHT] = !m_movement[RIGHT];
    }
    else if((flag_directions & FLAG_LEFT) == FLAG_LEFT)
    {
        m_movement[LEFT] = !m_movement[LEFT];
    }
}

int Entity::get_pos(int x_or_y)
{
    //on retourne la cooredonnée demandée
    return m_pos[x_or_y];
}

int Entity::get_border(int which_side)
{
    return m_sprite->get_border(which_side);
}

int Entity::get_angle()
{
    return m_angle;
}

int Entity::get_damage()
{
    return m_damages;
}

int Entity::get_speed()
{
    return m_speed;
}

int Entity::get_size(int h_or_w)
{
    return m_sprite->get_size(h_or_w);
}

Uint32 Entity::out_of_screen()
{
    Uint32 borders = FLAG_NONE;
    if(this->get_border(TOP) < TOP_BORDER_HIGHT)
    {
        borders = borders | FLAG_UP;
    }
    else if(this->get_border(BOTTOM) > m_GVC->screen()->h)
    {
        borders = borders | FLAG_DOWN;
    }
    if(this->get_border(LEFT) < 0)
    {
        borders = borders | FLAG_LEFT;
    }
    else if(this->get_border(RIGHT) > m_GVC->screen()->w)
    {
        borders = borders | FLAG_RIGHT;
    }

    if(borders != FLAG_NONE){m_parameters[IS_ON_BORDER] = true;}
    else{m_parameters[IS_ON_BORDER] = false;}

    return borders;
}

Uint32 Entity::get_type()
{
    return m_type;
}

bool Entity::collision(Entity *other)
{
    //si la collision est activée sur les deux entités
    if(!m_parameters[COLLISIONNABLE] or !other->get_parameter(COLLISIONNABLE))
    {
        return false;
    }

    //si les deux entités sont trop loins pour que la moindre collision soit possible
    if(Vector(m_pos[X], m_pos[Y], other->get_pos(X), other->get_pos(Y)).get_norm() > max(this->get_size(W), this->get_size(H)) +
                                                                                     max(other->get_size(W), other->get_size(H)))
    { //cela permet d'économiser nettement le processeur
        return false;
    }
    //sinon, si les deux entités ont une rotation simple (multiple de 90) ou aucune rotation
    else if(m_angle%90 == 0 and other->get_angle()%90 == 0)
    {
        //detection de collision simple basé sur les bordures des deux entités
        if(this->get_border(TOP) > other->get_border(BOTTOM) or
           this->get_border(BOTTOM) < other->get_border(TOP) or
           this->get_border(LEFT) > other->get_border(RIGHT) or
           this->get_border(RIGHT) < other->get_border(LEFT))
        {
            return false;
        }
        else{return true;}
    }
    //sinon on teste avec les hitbox précises
    else
    {
        return m_hitbox.collision(other->get_hitbox());
    }
}

bool Entity::get_parameter(int which_paremeter)
{
    return m_parameters[which_paremeter];
}

Hitbox* Entity::get_hitbox()
{
    return &m_hitbox;
}

void Entity::set_pos(int x, int y)
{
    //on change la position de l'entité par la nouvelle
    m_pos[X] = x;
    m_pos[Y] = y;
    //de meme pour le sprite
    m_sprite->set_pos(x,y);
}

void Entity::set_parameter(int which_parameter, bool enable)
{
    m_parameters[which_parameter] = enable;

    if(!m_parameters[ANIMATED])
    {
        m_sprite->set_animation(false);
    }
    if(which_parameter == BOOMERANG)
    {
        m_sprite->enable_boomrang_mode();
    }
}

void Entity::set_speed(int new_speed)
{
    m_speed = new_speed;
}

void Entity::manage()
{
    //on fait bouger le perso vers la où il doit de autant de pixel que sa vitesse l'indique suivant le temps écoulé depuis le dernier déplacement
    if(m_parameters[MOTION])
    {
        if(m_timer.get_elapsed_time() != 0)
        {
            if(m_movement[UP])
            {
                m_pos[Y] -= m_speed / m_timer.get_elapsed_time();
            }
            else if(m_movement[DOWN])
            {
                m_pos[Y] += m_speed / m_timer.get_elapsed_time();
            }
            if(m_movement[RIGHT])
            {
                m_pos[X] += m_speed / m_timer.get_elapsed_time();
            }
            else if(m_movement[LEFT])
            {
                m_pos[X] -= m_speed / m_timer.get_elapsed_time();
            }
            //et on adapte la positon de son sprite
            m_sprite->set_pos(m_pos[X], m_pos[Y]);
        }
    }

    //empecher de sortir de l'écran
    if(m_parameters[IN_SCREEN])
    {
        this->stay_in_screen(this->out_of_screen());
    }

    if(m_pos[Y] > m_GVC->screen()->h+500 or m_pos[Y] < -500){m_parameters[ALIVE] = false;}

    m_hitbox.update(m_pos[X], m_pos[Y]);

    m_timer.restart();
}

void Entity::display()
{
    //On affiche le sprite
    m_sprite->display();
    //Si le mode debug est activé on affiche la ligne de debug
    if(m_parameters[DEBUG_MODE])
    {
        m_hitbox.update(m_pos[X], m_pos[Y]);
        m_hitbox.show(m_GVC);
    }
}

void Entity::manage_and_display()
{
    //gère et affiche l'entité
    this->manage();
    this->display();
}

void Entity::show_debug_line()
{
    //on crée un rectangle qui trace deux lignes
    SDL_Rect debugLine;

    //la premiere verticale callé sur la position x de l'entité
    debugLine.w = 2;
    debugLine.h = m_GVC->screen()->h;
    debugLine.x = m_pos[X];
    debugLine.y = 0;

    //et on l'affiche
    SDL_SetRenderDrawColor(m_GVC->renderer(),255,255,255,0);
    SDL_RenderFillRect(m_GVC->renderer(), &debugLine);

    //la seconde horizontale callée sur la position y de l'entité
    debugLine.w = m_GVC->screen()->w;
    debugLine.h = 2;
    debugLine.x = 0;
    debugLine.y = m_pos[Y];

    //qu'on affiche également
    SDL_RenderFillRect(m_GVC->renderer(), &debugLine);

    m_hitbox.update(m_pos[X], m_pos[Y]);

    m_hitbox.show(m_GVC);
}

void Entity::spin(int angle)
{
    m_angle += angle;
    if(m_angle >= 360)
    {
        m_angle -= 360;
    }
    m_sprite->spin(angle);

    m_hitbox.update(m_pos[X], m_pos[Y]);

    m_hitbox.spin(angle);
}

void Entity::stay_in_screen(Uint32 borders)
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
    //on actualise la position du sprite
    m_sprite->set_pos(m_pos[X], m_pos[Y]);
}

void Entity::lose_hp(int lost_hp)
{
    m_parameters[ALIVE] = false;
}
