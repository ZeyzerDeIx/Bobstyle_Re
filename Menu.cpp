#include "Menu.h"
#include "Text_boxe.h"

using namespace std;

//[&](){this->enable_game();}

Menu::Menu(Global_variables_container* GVC, int button_number, int column_number, Sprite* screenshot)
{
    m_GVC = GVC;

    //cecei est un sdl_rect qui sert à rendre le haut de l'écran gris pour y afficher le titre
    m_info_bar_size.x = 0;
    m_info_bar_size.y = 0;
    m_info_bar_size.w = m_GVC->screen()->w;
    m_info_bar_size.h = TOP_BORDER_HIGHT;

    m_text = new Text(GVC, "Menu", 70); //création du texte servant de titre au menu
    m_text->change_text("SAME", true, 100); //on le souligne et on le met en rouge
    m_text->set_pos(m_GVC->screen()->w/2, TOP_BORDER_HIGHT/2); //on le place au centre haut

    //on créé autant de boutons que demandé
    for(int i = 0 ; i<button_number ; i++)
    {
        m_buttons.push_back(new Button(GVC, int_to_string(i+1)));
    }

    //on les place selon une disposition de haut en bas avec autant de colonnes que demandées
    for(int i = 0 ; i<column_number ; i++)
    {
        int k((m_buttons.size()+1)/column_number);
        int l(k);
        if(i+1 == column_number){l = m_buttons.size() - ((k)*i);}
        for(int j=0 ; j<l ; j++)
        {
            m_buttons[k*i+j]->set_pos(m_GVC->screen()->w/(column_number+1) * (i+1),
                                      (TOP_BORDER_HIGHT+(m_GVC->screen()->h-TOP_BORDER_HIGHT)/((l)*2) + (((m_GVC->screen()->h-TOP_BORDER_HIGHT))/(l) * j)));
        }
    }

    m_done = false;
    m_is_main_menu = false;

    m_screenshot = screenshot;
}

Menu::~Menu()
{
    if(m_is_main_menu){delete m_GVC;}

    delete m_screenshot;

    delete m_text;

    for(int i=0 ; i<m_buttons.size() ; i++)
    {
        delete m_buttons[i];
    }
}

int Menu::start()
{
    Handler handle_guy(m_GVC, this, &m_done);

    int timer = SDL_GetTicks();

    while(!m_done)
    {
        if(SDL_GetTicks() - timer >= MILISEC_PER_FRAME)
        {
            timer = SDL_GetTicks();

            //gestion de l'affichage et autres
            //{


            //rebouter l'écran
            SDL_SetRenderDrawColor(m_GVC->renderer(), BACK_SCREEN_COLOR_R, BACK_SCREEN_COLOR_G, BACK_SCREEN_COLOR_B, 0);
            SDL_RenderFillRect(m_GVC->renderer(), nullptr);

            if(m_screenshot != nullptr)
            {
                m_screenshot->display();
            }

            //afficher la barre d'info
            SDL_SetRenderDrawColor(m_GVC->renderer(),50,50,50,0);
            SDL_RenderFillRect(m_GVC->renderer(), &m_info_bar_size);

            m_text->display();

            this->display();

            //On actualise l'écran
            SDL_RenderPresent(m_GVC->renderer());

            //}
            //Fin de la gestion de l'affichage et autres
        }

        handle_guy.handle();

        SDL_Delay(1);
    }
    return 0;
}

void Menu::display()
{
    for(int i=0 ; i<m_buttons.size() ; i++)
    {
        m_buttons[i]->display();
    }
}

void Menu::click(int up_or_down)
{
    for(int i=0 ; i<m_buttons.size() ; i++)
    {
        if(m_buttons[i]->is_clicked())
        {
            this->call_for(m_buttons[i]->get_function(), i);
            m_buttons[i]->click(up_or_down);
            break;
        }
        m_buttons[i]->click(up_or_down);
    }
}

void Menu::set_button(int wich_button, int wich_function, string new_text)
{
    if(wich_button <= m_buttons.size())
    {
        m_buttons[wich_button-1]->rework(wich_function, new_text, 51 - new_text.size());
    }
    else
    {
        cerr << "Erreur: Tentative de modification d'un bouton inexistant!" << endl;
    }
}

void Menu::set_caption(string new_text)
{
    m_text->change_text(new_text, true, 100); //on change le texte et on le met en souligné et en rouge

    if(new_text == "Menu principal"){m_is_main_menu = true;}
}

void Menu::call_for(int wich_function, int button_number)
{
    switch(wich_function)
    {
        case F_QUIT:{
            m_done = true;
            break;}

        case F_GAME:{
            game(m_GVC);
            break;}

        case F_OPTIONS:{
            Menu option(m_GVC, 2);
            option.set_button(1, F_DIFFICULTY_CHOICE, "Choisir la difficulté");
            option.set_button(2, F_QUIT, "Retour");
            option.set_caption("Menu des options");

            option.start();
            break;}

        case F_DIFFICULTY_CHOICE:{
            Menu difficulty(m_GVC, 5);
            difficulty.set_button(1, F_SET_DIFFICULTY, "Trop facile");
            difficulty.set_button(2, F_SET_DIFFICULTY, "Facile");
            difficulty.set_button(3, F_SET_DIFFICULTY, "Normal");
            difficulty.set_button(4, F_SET_DIFFICULTY, "Difficile");
            difficulty.set_button(5, F_SET_DIFFICULTY, "Injuste");
            difficulty.set_caption("Choisir la difficulté");

            difficulty.start();
            break;}

        case F_SET_DIFFICULTY:{
            m_GVC->set_difficulty(button_number);
            m_done = true;
            break;}

        case F_SCORES_TABLE:{
            //cette variante de Menu n'a pas de bouton mais uniquement un texte sur plusieurs lignes
            Text_boxe displayer(m_GVC, sort_scores(get_saved_scores()), LEFT);
            displayer.set_caption("Tables de scores");

            displayer.start();
            break;}
    }
}
