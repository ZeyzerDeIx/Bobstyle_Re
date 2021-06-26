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
    m_text->change_text("SAME", true, 150, 30, 30); //on le souligne et on le met en rouge
    m_text->set_pos(m_GVC->screen()->w/2, TOP_BORDER_HIGHT/2); //on le place au centre haut

    //on créé autant de boutons que demandé
    for(int i = 0 ; i<button_number ; i++)
    {
        m_buttons.push_back(new Button(GVC, int_to_string(i+1)));
    }

    //on les place selon une disposition de haut en bas avec autant de colonnes que demandées
    for(int i = 0 ; i<column_number ; i++)
    {
        //on divise le nombre de bouton en un bon nombre de colonnes
        int k((m_buttons.size()+1)/column_number); //nombre de bouton par colonne
        //on l'enregistre dans une autre variable
        int l(k);
        //si on est à la derniere colonne l devient le nombre de bouton total moins le nombre de bouton par colonne fois le numéro de la derniere colonne
        if(i+1 == column_number){l = m_buttons.size() - (k*i);} //cela sert à savoir le vrai nombre de bouton sur la derniere colonne
        for(int j=0 ; j<l ; j++)
        {
            m_buttons[k*i+j]->set_pos(m_GVC->screen()->w/(column_number+1) * (i+1), //on place le bouton dans la bonne colonne
                                       //et dans la bonne ligne
                                      (TOP_BORDER_HIGHT+(m_GVC->screen()->h-TOP_BORDER_HIGHT)/((l)*2) + (((m_GVC->screen()->h-TOP_BORDER_HIGHT))/(l) * j)));
        }
    }

    m_done = false; //faux tant que le menu n'est pas fermé
    m_parameters[IS_MAIN_MENU] = false; //faux par defaut
    m_parameters[DELETE_SCREENSHOT] = false; //faux aussi par defaut

    m_screenshot = screenshot; //on sauvegarde la screenshot
}

Menu::~Menu()
{
    if(m_parameters[IS_MAIN_MENU]){delete m_GVC;} //si ce menu est le principal, il supprime le GVC (car fin du programme)

    if(m_parameters[DELETE_SCREENSHOT]){delete m_screenshot;} //si on doit supprimer la screenshot on le fait

    delete m_text; //on supprime le texte

    for(int i=0 ; i<m_buttons.size() ; i++)
    {
        delete m_buttons[i]; //on supprime les boutons
    }
}

int Menu::start()
{
    Handler handle_guy(m_GVC, this, &m_done); //on créer un handler qui va reconaitre le menu et se configurer en conséquence

    Timer timer; //on créer un chronomètre

    while(!m_done)
    {
        if(timer.get_elapsed_time() >= MILISEC_PER_FRAME) //si on a passé un frame
        {
            timer.restart(); //on reset le chronomètre

            //gestion de l'affichage et autres
            //{


            //rebouter l'écran
            SDL_SetRenderDrawColor(m_GVC->renderer(), BACK_SCREEN_COLOR_R, BACK_SCREEN_COLOR_G, BACK_SCREEN_COLOR_B, 0); //on choisit la couleur
            SDL_RenderFillRect(m_GVC->renderer(), 0); //on en remplit l'écran

            //si on a une screenshot on l'affiche en arrière plan
            if(m_screenshot != 0)
            {
                m_screenshot->display();
            }

            //afficher la barre d'info
            SDL_SetRenderDrawColor(m_GVC->renderer(),50,50,50,0); //couleur grise
            SDL_RenderFillRect(m_GVC->renderer(), &m_info_bar_size); //on affiche la bande grise

            m_text->display(); //on affiche le titre du menu

            this->display(); //on affiche les boutons

            //On actualise l'écran
            SDL_RenderPresent(m_GVC->renderer());

            //}
            //Fin de la gestion de l'affichage et autres
        }

        handle_guy.handle(); //on gère les entré

        SDL_Delay(1); //on laisse le temps au cpu de faire autre chose
    }
    return 0;
}

void Menu::display()
{
    for(int i=0 ; i<m_buttons.size() ; i++)
    {
        m_buttons[i]->display(); //on affiche les boutons
    }
}

void Menu::click(int up_or_down)
{ //quand l'utilisateur click
    for(int i=0 ; i<m_buttons.size() ; i++)
    { //on regarde tous les boutons
        if(m_buttons[i]->is_clicked())
        { //on demande à tous les boutons si le curseur est sur eux
            this->call_for(m_buttons[i]->get_function(), i); //on appel leur fonction
            m_buttons[i]->click(up_or_down); //on change son état visuel
            break; //on quitte la boucle au premier click
        }
        m_buttons[i]->click(up_or_down); //on reset les boutons
    }
}

void Menu::set_button(int which_button, int which_function, string new_text, int wich_slot)
{ //permet de modifier le texte et la fonction d'un bouton
    if(which_button <= m_buttons.size())
    { //on revoit le bon bouton
        m_buttons[which_button-1]->rework(which_function, new_text);
    }
    else
    { //si on est hors du nombre de bouton on affiche un message d'erreur
        cerr << "Erreur: Tentative de modification d'un bouton inexistant!" << endl;
    }
}

void Menu::add_button_function(int which_button, int which_function, string new_text)
{ //on ajoute un text et une fonction à un bouton
    if(which_button <= m_buttons.size())
    {
        m_buttons[which_button-1]->add_function(which_function, new_text);
    }
    else
    { //si on est hors du nombre de bouton on affiche un message d'erreur
        cerr << "Erreur: Tentative de modification d'un bouton inexistant!" << endl;
    }
}

void Menu::set_caption(string new_text)
{
    m_text->change_text(new_text, true, 150, 30, 30); //on change le texte et on le met en souligné et en rouge
}

//permet de modifier un paramètre
void Menu::set_parameter(int which_parameter, bool enable){m_parameters[which_parameter] = enable;}



void Menu::call_for(int which_function, int button_number)
{ //appel une fonction pour un bouton
    switch(which_function)
    {
        case F_QUIT:{ //Met fin au menu, le quitte
            m_done = true;
            break;}

        case F_GAME:{ //Lance une partie
            game(m_GVC);
            break;}

        case F_OPTIONS:{ //Créer un menu "options"
            Menu option(m_GVC, 5, 1, m_screenshot);
            option.set_button(1, F_DIFFICULTY_CHOICE, "Choisir la difficulté");

            if(!m_GVC->get_game_parameter(P_MISSILES_ON))
            {
                option.set_button(2, F_SWITCH_MISSILES, "Activer les missiles");
                option.add_button_function(2, F_SWITCH_MISSILES, "Désactiver les missiles");
            }
            else
            {
                option.set_button(2, F_SWITCH_MISSILES, "Désactiver les missiles");
                option.add_button_function(2, F_SWITCH_MISSILES, "Activer les missiles");
            }

            if(!m_GVC->get_game_parameter(P_DEBRIS_ON))
            {
                option.set_button(3, F_SWITCH_DEBRIS, "Activer les débris");
                option.add_button_function(3, F_SWITCH_DEBRIS, "Désactiver les débris");
            }
            else
            {
                option.set_button(3, F_SWITCH_DEBRIS, "Désactiver les débris");
                option.add_button_function(3, F_SWITCH_DEBRIS, "Activer les débris");
            }

            option.set_button(4, F_USE_DEBUG_ROOM, "Debug room");

            option.set_button(5, F_QUIT, "Retour");
            option.set_caption("Menu des options");

            option.start();
            break;}

        case F_DIFFICULTY_CHOICE:{ //Créer un menu de selection de difficulté
            Menu difficulty(m_GVC, 5, 1, m_screenshot);
            difficulty.set_button(1, F_SET_DIFFICULTY, "Trop facile");
            difficulty.set_button(2, F_SET_DIFFICULTY, "Facile");
            difficulty.set_button(3, F_SET_DIFFICULTY, "Normal");
            difficulty.set_button(4, F_SET_DIFFICULTY, "Difficile");
            difficulty.set_button(5, F_SET_DIFFICULTY, "Injuste");
            difficulty.set_caption("Choisir la difficulté");

            difficulty.start();
            break;}

        case F_SET_DIFFICULTY:{ //Permet de changer la difficulté selon le nombre du bouton dans la liste du menu
            m_GVC->set_difficulty(button_number);
            m_done = true;
            break;}

        case F_SCORES_TABLE:{ //Affiche la table des scores dans l'ordre décroissant
            //cette variante de Menu n'a pas de bouton mais uniquement un texte sur plusieurs lignes
            Text_boxe displayer(m_GVC, sort_scores(get_saved_scores()), LEFT);
            displayer.set_caption("Tables de scores");

            displayer.start();
            break;}

        case F_SWITCH_MISSILES:{ //active/désactive les missiles
            m_GVC->set_game_parameter(P_MISSILES_ON, !m_GVC->get_game_parameter(P_MISSILES_ON));
            break;}

        case F_SWITCH_DEBRIS:{ //active/désactive les débris
            m_GVC->set_game_parameter(P_DEBRIS_ON, !m_GVC->get_game_parameter(P_DEBRIS_ON));
            break;}

        case F_USE_DEBUG_ROOM:{ //lance une partie en debug room
            debug_room(m_GVC);
            break;}
    }
}
