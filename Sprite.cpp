#include "Sprite.h"

using namespace std;

Sprite::Sprite()
{
    //place le sprite au centre de l'écran apr defaut
    m_pos[X] = 0;
    m_pos[Y] = 0;
    m_angle = 0; //la roation est nule par defaut
}

Sprite::Sprite(Global_variables_container* GVC)
{
    m_GVC = GVC;

    m_image = 0;
    m_original_image = 0;

    //place le sprite au centre de l'écran apr defaut
    m_pos[X] = m_GVC->screen()->w/2;
    m_pos[Y] = m_GVC->screen()->h/2;

    //la roation est nule par defaut
    m_angle = 0;
}

Sprite::Sprite(Global_variables_container* GVC, SDL_Surface* image)
{
    m_GVC = GVC;

    m_original_image = SDL_ConvertSurface(image, image->format, 0); //charge l'image dans une surface
    //on ne gère par les transparence car c'est en principe déjà fait
    //on en fait une texture
    m_image = SDL_CreateTextureFromSurface(m_GVC->renderer(), m_original_image); //charge l'image

    //place le sprite au centre de l'écran apr defaut
    m_pos[X] = m_GVC->screen()->w/2;
    m_pos[Y] = m_GVC->screen()->h/2;

    m_angle = 0; //la roation est nule par defaut
}

Sprite::Sprite(Global_variables_container* GVC, string image_location)
{
    m_GVC = GVC;

    m_original_image = SDL_LoadBMP(image_location.c_str()); //charge l'image dans une surface
    //On fait disparaitre la couleur de transparence (definie comme étant 255,25,255) sur l'image originale
    SDL_SetColorKey(m_original_image, SDL_TRUE, SDL_MapRGB(m_original_image->format, 125, 25, 125));
    //on en fait une texture
    m_image = SDL_CreateTextureFromSurface(m_GVC->renderer(), m_original_image);

    if(m_original_image == NULL)
    {
        cerr << "Erreur: L'image n'a pas chargée: SDL error: " << SDL_GetError();
    }
    //place le sprite au centre de l'écran apr defaut
    m_pos[X] = m_GVC->screen()->w/2;
    m_pos[Y] = m_GVC->screen()->h/2;
    m_angle = 0; //la roation est nule par defaut
    //On fait disparaitre la couleur de transparence (definie comme étant 255,25,255) sur les deux sprites
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(m_image);
    SDL_FreeSurface(m_original_image);
}

Sprite* Sprite::self_copy()
{
    return new Sprite(m_GVC, m_original_image);
}

void Sprite::load_new_surface(SDL_Surface* new_image)
{
    SDL_DestroyTexture(m_image);
    m_image = SDL_CreateTextureFromSurface(m_GVC->renderer(), new_image);
}

void Sprite::reset_image()
{
    SDL_DestroyTexture(m_image);
    m_image = SDL_CreateTextureFromSurface(m_GVC->renderer(), m_original_image);
}

bool Sprite::presence_of_bugs()
{
    return m_image == 0;
}

int Sprite::get_border(int wich_side)
{
    //Retourne la valeure (X ou Y) correspondante à la bordure demandée.
    int w,h;
    SDL_QueryTexture(m_image, nullptr, nullptr, &w, &h);
    switch(wich_side)
    {
        case TOP:
            return m_pos[Y] - h/2;
            break;
        case BOTTOM:
            return m_pos[Y] + h/2;
            break;
        case LEFT:
            return m_pos[X] - w/2;
            break;
        case RIGHT:
            return m_pos[X] + w/2;
            break;
        default:
            return 0;
    }
}

int Sprite::get_pos(int x_or_y)
{
    //retourne la coordonnée demandée
    return m_pos[x_or_y];
}

int Sprite::get_size(int h_or_w)
{
    if(h_or_w == H)
    {
        return this->get_border(BOTTOM) - this->get_border(TOP);
    }
    else if(h_or_w == W)
    {
        return this->get_border(RIGHT) - this->get_border(LEFT);
    }
    return 0;
}

SDL_Surface* Sprite::get_original_image()
{
    return m_original_image;
}

void Sprite::set_pos(int x, int y)
{
    //change la position
    m_pos[X] = x;
    m_pos[Y] = y;
}

void Sprite::set_debug_mode(bool debug_mode)
{
    m_debug_mode = debug_mode;
}

void Sprite::display()
{
    //affiche le bord haut gauche du sprite à mis distance du centre
    SDL_Rect showing_rect;
    showing_rect.x = m_pos[X] - m_original_image->w/2;
    showing_rect.y = m_pos[Y] - m_original_image->h/2;
    showing_rect.w = m_original_image->w;
    showing_rect.h = m_original_image->h;

    //affiche l'image sur l'écran avec une rotation de m_angle degrés
    SDL_RenderCopyEx(m_GVC->renderer(), m_image, nullptr, &showing_rect, m_angle, nullptr, SDL_FLIP_NONE);
}

void Sprite::spin(int angle)
{
    //fait tourner le sprite et enregistre son nouvel angle
    m_angle -= angle;
    if(m_angle >= 360)
    {
        m_angle -= 360;
    }
}

void Sprite::reset_angle()
{
    m_angle = 0;
}












Animated_sprite::Animated_sprite(){}

Animated_sprite::Animated_sprite(Global_variables_container* GVC, std::string image_location, int number_of_phase = 1): Sprite(GVC, image_location)
{
    m_GVC = GVC;
    m_number_of_phase = number_of_phase;

    //on charge l'image originelle
    m_original_image = SDL_LoadBMP(image_location.c_str());
    //on verifie qu'elle s'est bien chargée
    if(m_original_image == NULL)
    {
        cerr << "Erreur: L'image n'a pas chargée: SDL error: " << SDL_GetError();
    }

    //on créé une "paire de ciseaux" pour decouper nos images
    SDL_Rect cutter;
    cutter.x = 0;
    cutter.y = 0;
    cutter.w = m_original_image->w/m_number_of_phase;
    cutter.h = m_original_image->h;

    //ici on créé le tableau des phases
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        //on ajuste les coordonnées de notre "paire de ciseaux"
        cutter.x = i*(m_original_image->w/m_number_of_phase);
        //on créé un pointeur temporaire vers une nouvelle surface
        SDL_Surface* temporary_surface = new SDL_Surface;
        //on créé ladite nouvelle surface à la bonne taille
        temporary_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,  cutter.w, cutter.h,  32,  0,  0,  0,  0);
        //on y copie l'image originelle
        SDL_BlitSurface(m_original_image, &cutter, temporary_surface, NULL);
        //on gère la transaparence
        SDL_SetColorKey(temporary_surface, SDL_TRUE, SDL_MapRGB(temporary_surface->format, 125, 25, 125));
        //on charge l'image dnas un nouveau Sprite que l'on ajoute au tableau des phases
        m_phases.push_back(new Sprite(m_GVC, temporary_surface));
        //on libère la mémoire car 'temporary_surface' est un pointeur alloué dynamiquement
        SDL_FreeSurface(temporary_surface);
    }

    //on établie que la phase actuelle est la phase 0
    m_current = 0;

    //par defaut l'animation est activée
    m_animation_enable = true;

    //par defaut la vitesse est d'un sprite/frame
    m_animation_speed = 1;

    //claire
    m_frame_counter = 0;
}

Animated_sprite::~Animated_sprite()
{ //suppirme tout le tableau des phases pour liberer la mémoire
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        if(m_phases[i] != 0)
        {
            delete m_phases[i];
        }
    }
}

int Animated_sprite::get_pos(int x_or_y)
{ //retourne la position du sprite actuellement affiché
    return m_phases[m_current]->get_pos(x_or_y);
}

int Animated_sprite::get_border(int witch_side)
{ //retourne le bord du sprite actuellement affiché
    return m_phases[m_current]->get_border(witch_side);
}

int Animated_sprite::get_size(int h_or_w)
{
    return m_phases[m_current]->get_size(h_or_w);
}

bool Animated_sprite::presence_of_bugs()
{
    bool test = false;
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        test = test or m_phases[i]->presence_of_bugs();
    }
    return test;
}

Sprite* Animated_sprite::operator[](int key)
{
    if(key < 0)
    {
        return m_phases[m_phases.size()-1];
    }
    else
    {
        return m_phases[key];
    }
}

void Animated_sprite::set_debug_mode(bool debug_mode) //active ou desactive le mode debug
{ //on active le debug mode pour toutes les phases
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        m_phases[i]->set_debug_mode(debug_mode);
    }
}

void Animated_sprite::set_pos(int x, int y) //active ou desactive le mode debug
{ //retourne les coordonnées du cnetre du sprite actuellemen affiché
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        m_phases[i]->set_pos(x,y);
    }
}

void Animated_sprite::set_animation(bool enable)
{
    m_animation_enable = enable;
}

void Animated_sprite::reset_animation()
{
    m_current = 0;
}

void Animated_sprite::set_anim_speed(int speed)
{
    m_animation_speed = speed;
}

void Animated_sprite::reset_angle()
{
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        m_phases[i]->reset_angle();
    }
}

void Animated_sprite::enable_boomrang_mode()
{
    //on copie toutes les phases et on les ajoute à la fin du tableau en ordre inverse
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        m_phases.push_back(m_phases[m_number_of_phase - 1 - i]->self_copy());
    }
    //ensuite on actualise le fait que la tableau des phases est maintenant 2 fois plus grand
    m_number_of_phase *= 2;
}

void Animated_sprite::display()
{ //on affiche le sprite actuelle
    m_phases[m_current]->display();
    //on incrémente la phase vers la suivante
    if(m_animation_enable)
    {
        m_frame_counter ++;
        if(m_frame_counter >= m_animation_speed)
        {
            m_frame_counter = 0;
            this->skip_phase(1);
        }
    }
}

void Animated_sprite::spin(int angle)
{ //on fait tourner toutes les phases de l'angle demandé
    for(int i=0 ; i<m_number_of_phase ; i++)
    {
        m_phases[i]->spin(angle);
    }
}

void Animated_sprite::skip_phase(int number)
{ //on incrémente le compteur de phases
    m_current += number;
    if(m_current >= m_number_of_phase)
    { //et si il est supperrieur au nombre de phases on le reset
        m_current = 0;
    }
}
