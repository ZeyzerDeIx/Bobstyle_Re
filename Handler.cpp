#include "Handler.h"

using namespace std;

Handler::Handler()
{
    m_GVC = nullptr;
    m_done = nullptr;
    m_bobstyle = nullptr;
    m_interface = nullptr;
    m_mode = 1000;
    m_text = nullptr;
    m_menu = nullptr;
    m_ctrl = false;
}

Handler::Handler(Global_variables_container* GVC, Bobstyle* bobstyle, Interface* interf, Generator* generator, bool* done)
{
    m_GVC = GVC;
    m_done = done;
    m_bobstyle = bobstyle;
    m_interface = interf;
    m_generator = generator;
    m_mode = GAME;
    m_text = nullptr;
    m_menu = nullptr;
    m_ctrl = false;
}

Handler::Handler(Global_variables_container* GVC, Menu* menu, bool* done)
{
    m_GVC = GVC;
    m_done = done;
    m_bobstyle = nullptr;
    m_interface = nullptr;
    m_mode = MENU;
    m_text = nullptr;
    m_menu = menu;
    m_ctrl = false;
}

Handler::Handler(Global_variables_container* GVC, string* text, bool* done)
{
    m_GVC = GVC;
    m_done = done;
    m_bobstyle = nullptr;
    m_interface = nullptr;
    m_mode = WRITE;
    m_text = text;
    m_menu = nullptr;
    m_ctrl = false;
}

void Handler::handle()
{
    //boucle de gestion des evennements
    while(SDL_PollEvent(&m_event))
    {
        if(m_mode == GAME){
        switch(m_event.type)
        {
            //Si l'utilisateur clique sur la croix pour fermer la fenêtre
            case SDL_QUIT:
                *m_done = true;
                break;

            //Si le curseur bouge
            case SDL_MOUSEMOTION:
                m_GVC->set_cursor_pos(m_event.motion.x, m_event.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(m_event.button.button == SDL_BUTTON_LEFT)
                {
                    m_bobstyle->dash();
                }
                break;

            //Si une touche est appuyée
            case SDL_KEYDOWN:
                switch(this->event_validation(m_event.key.keysym.sym))
                {
                    //echape
                    case  SDLK_ESCAPE:
                        *m_done = true;
                        break;
                    //la touche flèche du haut
                    case SDLK_UP:
                        m_bobstyle->set_movement(FLAG_UP);
                        break;
                    //la touche flèche du bas
                    case SDLK_DOWN:
                        m_bobstyle->set_movement(FLAG_DOWN);
                        break;
                    //la touche flèche de gauche
                    case SDLK_LEFT:
                        m_bobstyle->set_movement(FLAG_LEFT);
                        break;
                    //la touche flèche de droite
                    case SDLK_RIGHT:
                        m_bobstyle->set_movement(FLAG_RIGHT);
                        break;
                    //la touche z
                    case SDLK_z:
                        m_bobstyle->set_movement(FLAG_UP);
                        break;
                    //la touche s
                    case SDLK_s:
                        m_bobstyle->set_movement(FLAG_DOWN);
                        break;
                    //la touche q
                    case SDLK_q:
                        m_bobstyle->set_movement(FLAG_LEFT);
                        break;
                    //la touche d
                    case SDLK_d:
                        m_bobstyle->set_movement(FLAG_RIGHT);
                        break;
                    //le shift gauche
                    case SDLK_LSHIFT:
                        if(!m_ctrl)
                        {
                            m_bobstyle->set_speed(m_bobstyle->get_speed()*2);
                        }
                        else
                        {
                            m_generator->set_debug_mode(!m_generator->get_debug_mode());
                            m_bobstyle->set_parameter(DEBUG_MODE, !m_bobstyle->get_parameter(DEBUG_MODE));
                        }
                        break;
                    case SDLK_LCTRL:
                        m_ctrl = true;
                        break;
                    case SDLK_g:
                        m_generator->generate_entities(DEBRIS);
                        break;
                    case SDLK_F2:
                        save_screenshot(m_GVC);
                        break;
                    default:
                        0;
                } //fin du switch des touches appuyées
                break;

            //Si une touche est relachée
            case SDL_KEYUP:
                this->event_validation(m_event.key.keysym.sym, true);
                switch(m_event.key.keysym.sym)
                {
                    //la touche flèche du haut
                    case SDLK_UP:
                        m_bobstyle->set_movement(FLAG_UP);
                        break;
                    //la touche flèche du bas
                    case SDLK_DOWN:
                        m_bobstyle->set_movement(FLAG_DOWN);
                        break;
                    //la touche flèche de gauche
                    case SDLK_LEFT:
                        m_bobstyle->set_movement(FLAG_LEFT);
                        break;
                    //la touche flèche de droite
                    case SDLK_RIGHT:
                        m_bobstyle->set_movement(FLAG_RIGHT);
                        break;
                    //la touche z
                    case SDLK_z:
                        m_bobstyle->set_movement(FLAG_UP);
                        break;
                    //la touche s
                    case SDLK_s:
                        m_bobstyle->set_movement(FLAG_DOWN);
                        break;
                    //la touche q
                    case SDLK_q:
                        m_bobstyle->set_movement(FLAG_LEFT);
                        break;
                    //la touche d
                    case SDLK_d:
                        m_bobstyle->set_movement(FLAG_RIGHT);
                        break;
                    case SDLK_LSHIFT:
                        m_bobstyle->set_speed(m_bobstyle->get_speed()/2);
                        break;
                    case SDLK_LCTRL:
                        m_ctrl = false;
                        break;
                    case SDLK_SPACE:
                        m_interface->pause();
                        break;
                    default:
                        0;
                } //fin du switch des touches relachées
                break;

        } } //fin du switch globale de GAME

        else if(m_mode == MENU){
        switch(m_event.type)
        {
            //Si l'utilisateur clique sur la croix pour fermer la fenêtre
            case SDL_QUIT:
                *m_done = true;
                break;

            //Si le curseur bouge
            case SDL_MOUSEMOTION:
                m_GVC->set_cursor_pos(m_event.motion.x, m_event.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(m_event.button.button == SDL_BUTTON_LEFT)
                {
                    m_menu->click(DOWN);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(m_event.button.button == SDL_BUTTON_LEFT)
                {
                    m_menu->click(UP);
                }
                break;

            //Si une touche est appuyée
            case SDL_KEYDOWN:
                switch(this->event_validation(m_event.key.keysym.sym))
                {
                    //echape
                    case  SDLK_ESCAPE:
                        *m_done = true;
                        break;
                    case SDLK_RETURN:
                        game(m_GVC); //lance une partie en normale par defaut
                        break;
                    case SDLK_F2:
                        save_screenshot(m_GVC);
                        break;
                    default:
                        0;
                } //fin du switch des touches appuyées
                break;

            //Si une touche est relachée
            case SDL_KEYUP:
                this->event_validation(m_event.key.keysym.sym, true);

                switch(m_event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        *m_done = true;
                        break;
                    default:
                        0;
                } //fin du switch des touches relachées
                break;
        } } //fin du switch globale de MENU

        else if(m_mode == WRITE){
        switch(m_event.type)
        {
            //Si l'utilisateur clique sur la croix pour fermer la fenêtre
            case SDL_QUIT:
                *m_done = true;
                break;

            //Si une touche est appuyée
            case SDL_KEYDOWN:

                if(m_event.key.keysym.sym == SDLK_BACKSPACE and m_timer.get_elapsed_time() >= 25)
                {
                    this->event_validation(m_event.key.keysym.sym, true);
                }

                switch(this->event_validation(m_event.key.keysym.sym))
                {
                    //echape
                    case  SDLK_ESCAPE:
                        *m_done = true;
                        *m_text = "skip";
                        break;
                    case SDLK_RETURN:
                        *m_done = true;
                        break;
                    case SDLK_BACKSPACE:
                        if(m_text->size() > 0){m_text->resize(m_text->size()-1);}
                        m_timer.restart();
                        break;
                    case SDLK_LSHIFT:
                        m_ctrl = true; //ici on utilise m_ctrl pour la touche shift (ça évite de refarie un bool en plus)
                        break;
                    case SDLK_F2:
                        save_screenshot(m_GVC);
                        break;
                    default:
                        *m_text += input_to_alpha(m_event.key.keysym.sym, m_ctrl);
                } //fin du switch des touches appuyées
                break;

            //Si une touche est relachée
            case SDL_KEYUP:
                this->event_validation(m_event.key.keysym.sym, true);

                switch(m_event.key.keysym.sym)
                {
                    case SDLK_LSHIFT:
                        m_ctrl = false;
                        break;
                    default:
                        0;
                } //fin du switch des touches relachées
                break;
        } } //fin du switch globale de WRITE

    } //fin de la boucle de gestion des evennements
}

int Handler::wait()
{
    SDL_WaitEvent(&m_event);
    if(m_event.type == SDL_KEYDOWN)
    {
        return m_event.key.keysym.sym;
    }
    return m_event.type;
}

int Handler::event_validation(int event, bool keyup)
{
    if(keyup == true)
    {
        m_dictionary[event] = false;
    }
    else if(m_dictionary[event] != true)
    {
        m_dictionary[event] = true;
        return event;
    }
    return INFINITE;
}

bool Handler::search_entry(int searched_entry)
{
    //boucle de gestion des evennements
    while(SDL_PollEvent(&m_event))
    {
        if(m_event.type == searched_entry)
        {
            return true;
        }
    } //fin de la boucle de gestion des evennements
    return false;
}

bool Handler::search_key(int searched_key)
{
    //boucle de gestion des evennements
    while(SDL_PollEvent(&m_event))
    {
        if(m_event.key.keysym.sym == searched_key)
        {
            return true;
        }
    } //fin de la boucle de gestion des evennements
    return false;
}
