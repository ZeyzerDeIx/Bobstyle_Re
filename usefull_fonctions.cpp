#include "usefull_fonctions.h"
#include "Handler.h"
#include "Text.h"

using namespace std;

//Fonctions
Global_variables_container* start_SDL()
{
    // initialiser SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cerr << "Erreur: Impossible de démarrer la SDL: " << SDL_GetError();
        return NULL;
    }
    TTF_Init();
    atexit(TTF_Quit);
    atexit(SDL_Quit);

    SDL_Window* window = SDL_CreateWindow("BOBSTYLE::RE",
                              SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                              0,0,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    Global_variables_container* GVC = new Global_variables_container(window,
                                    SDL_GetWindowSurface(window),
                                    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ));

    return GVC;
}

void save_screenshot(Global_variables_container* const GVC)
{
    SDL_Surface* screenshot = SDL_CreateRGBSurface(0, GVC->screen()->w, GVC->screen()->h, 32, 0,0,0,0);

    SDL_RenderReadPixels(GVC->renderer(), NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);

    SDL_SaveBMP(screenshot, "screenshot.bmp");
    SDL_FreeSurface(screenshot);
}

void save(string const name, int const score)
{
    ofstream save_file("Save/scores.csv", ios::app);

    if(save_file) //si on arrive à ouvrir le fichier de sauvgarde
    {
        if(name != "skip"){save_file << name << "," << score << endl;} //si l'utilisateur a rentré un nom on sauvegarde son score
    }
    else{cerr << "Erreur: Impossible d'ouvrir le fichier de sauvegarde en écriture." << endl;} //si le fichier ne s'ouvre pas
}

void draw_a_line(Global_variables_container* GVC, double a, int b)
{
    Pixel_killer kill_pixel(GVC->renderer());

    int y(0);
    int x(0);
    if(a<INFINITE)
    {
        if(a<=1 and a>=-1)
        {
            for(x=0 ; x<GVC->screen()->w ; x++)
            {
                y = a*x+b;
                if(y >= 0 and y <= GVC->screen()->h)
                {
                    kill_pixel(x,y);
                }
            }
        }
        else
        {
            for(y=0 ; y<GVC->screen()->h ; y++)
            {
                x = (y-b)/a;
                if(x >= 0 and x <= GVC->screen()->w)
                {
                    kill_pixel(x,y);
                }
            }
        }
    }
    else
    {
        for(y=0 ; y<GVC->screen()->h ; y++)
        {
            kill_pixel(b,y);
        }
    }
}
void draw_a_line(Global_variables_container* GVC, double a, int b, int a_x, int a_y, int b_x, int b_y)
{
    Pixel_killer kill_pixel(GVC->renderer());

    int x,y;
    if(a<INFINITE)
    {
        if(a<=1 and a>=-1)
        {
            for(x=min(a_x,b_x) ; x<max(a_x,b_x) ; x++)
            {
                y = a*x+b;
                if(y >= 0 and y <= GVC->screen()->h)
                {
                    kill_pixel(x,y);
                }
            }
        }
        else
        {
            for(y=min(a_y,b_y) ; y<max(a_y,b_y) ; y++)
            {
                x = (y-b)/a;
                if(x >= 0 and x <= GVC->screen()->w)
                {
                    kill_pixel(x,y);
                }
            }
        }
    }
    else
    {
        for(y=min(a_y,b_y) ; y<max(a_y,b_y)  ; y++)
        {
            kill_pixel(b,y);
        }
    }
}

void draw_box(Global_variables_container* GVC, int w, int h, int border_width)
{
    SDL_Rect rect;
    rect.w = w + border_width;
    rect.h = h + border_width;
    rect.x = GVC->screen()->w/2-w/2 - border_width/2;
    rect.y = GVC->screen()->h/2-h/2 - border_width/2;

    SDL_SetRenderDrawColor(GVC->renderer(), 10, 10, 10, 0);
    SDL_RenderFillRect(GVC->renderer(), &rect);

    rect.w -= border_width;
    rect.h -= border_width;
    rect.x += border_width/2;
    rect.y += border_width/2;

    SDL_SetRenderDrawColor(GVC->renderer(), 60, 60, 60, 0);
    SDL_RenderFillRect(GVC->renderer(), &rect);
}

Sprite* screenshot(Global_variables_container* GVC, int alpha)
{
    SDL_Surface* screenshot = SDL_CreateRGBSurfaceWithFormat(0, GVC->screen()->w, GVC->screen()->h, 32, SDL_PIXELFORMAT_BGRA32);
    SDL_Surface* black_filter = SDL_CreateRGBSurfaceWithFormat(0, GVC->screen()->w, GVC->screen()->h, 32, SDL_PIXELFORMAT_BGRA32);

    SDL_RenderReadPixels(GVC->renderer(), NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);

    SDL_FillRect(black_filter, NULL, SDL_MapRGBA(black_filter->format, 0, 0, 0, alpha));

    SDL_BlitSurface(black_filter, NULL, screenshot, NULL);

    Sprite* srnsht_sprite = new Sprite(GVC, screenshot);

    SDL_FreeSurface(screenshot);
    SDL_FreeSurface(black_filter);

    return srnsht_sprite;
}

SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

string int_to_string(int number)
{
    ostringstream conv;
    conv << number;
    return conv.str();
}

string enter_text(Global_variables_container* GVC, string prevent_text)
{
    Sprite* back_screen = screenshot(GVC, 100);

    SDL_Rect text_field_size;
    text_field_size.x = 0;
    text_field_size.y = GVC->screen()->h/2 - TOP_BORDER_HIGHT/2;
    text_field_size.w = GVC->screen()->w;
    text_field_size.h = TOP_BORDER_HIGHT;

    string text_to_return("");

    bool done(false);

    Handler handle_guy(GVC, &text_to_return, &done);

    Text entered_text(GVC);

    entered_text.change_text(prevent_text, false, 130, 130, 130);
    SDL_SetRenderDrawColor(GVC->renderer(),0,0,0,200); //on choisit la couleur à utiliser pour le champ du texte
    SDL_SetRenderDrawBlendMode(GVC->renderer(), SDL_BLENDMODE_BLEND); //active la transparence

    while(!done)
    {
        back_screen->display();

        SDL_RenderFillRect(GVC->renderer(), &text_field_size); //et on l'affiche

        if(text_to_return.size() != 0)
        {
            entered_text.change_text(text_to_return, false, 130, 130, 130);
        }
        else
        {
            entered_text.change_text(prevent_text, false, 130, 130, 130);
        }

        entered_text.display();

        //On actualise l'écran
        SDL_RenderPresent(GVC->renderer());

        handle_guy.handle();
    }

    SDL_SetRenderDrawBlendMode(GVC->renderer(), SDL_BLENDMODE_NONE); //désactive la transparence

    delete back_screen;

    if(text_to_return.size() == 0)
    {
        text_to_return = "skip";
    }

    return text_to_return;
}

string sort_scores(map<string, int> scores_table)
{
    string scores_text("");

    map<string, int>::iterator save_it;

    if(scores_table.size() == 0){scores_text+="Aucun score";scores_text+=ENTER;scores_text +="enregistré dans";scores_text +=ENTER;scores_text +="le fichier de";scores_text +=ENTER;scores_text +="sauvegarde";}

    while(scores_table.size() > 0)
    {
        save_it = scores_table.begin();
        for(map<string, int>::iterator it = scores_table.begin() ; it != scores_table.end() ; ++it)
        {
            if(it->second > save_it->second)
            {
                save_it = it;
            }
        }
        scores_text += save_it->first;
        scores_text += " : ";
        scores_text += int_to_string(save_it->second);
        scores_text += ENTER;
        scores_table.erase(save_it);
    }
    return scores_text;
}

int debris_rand()
{
    int const rdm(rand() % 100);
    if(rdm <= 30){return TINY;}
    else if(rdm <= 60){return SMALL;}
    else if(rdm <= 80){return MEDIUM;}
    else{return BIG;}
}

int string_to_int(string text)
{
    istringstream conv(text);

    int number;

    conv >> number;

    return number;
}

map<string, int> get_saved_scores()
{
    ifstream save_file("Save/scores.csv");

    string line("");

    map<string, int> scores_table;

    if(save_file) //si on arrive à ouvrir le fichier de sauvgarde
    {
        if(getline(save_file, line) and line == "Name,Score") //si l'entête est la bonne
        {
            while(getline(save_file, line)) //on lit tous les scores ligne par ligne
            {
                string name("");
                string str_score("");

                for(int i = 0 ; i<line.size() ; i++) //on parcourt la ligne
                {
                    if(isdigit(line[i]))
                    {
                        str_score += line[i];
                    }
                    else if(line[i] != ',')
                    {
                        name += line[i];
                    }
                }

                scores_table[name] = string_to_int(str_score);
            }
        }
    }
    else{cerr << "Erreur: Impossible d'ouvrir le fichier de sauvegarde en lecture." << endl;} //si le fichier ne s'ouvre pas

    return scores_table;
}




//Foncteurs
Pixel_killer::Pixel_killer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
    m_pixel_rect.x = 0;
    m_pixel_rect.y = 0;
    m_pixel_rect.w = 1;
    m_pixel_rect.h = 1;
}

void Pixel_killer::operator()(int x, int y, int R, int G, int B)
{
    m_pixel_rect.x = x;
    m_pixel_rect.y = y;
    SDL_SetRenderDrawColor(m_renderer,R,G,B,0);
    SDL_RenderFillRect(m_renderer, &m_pixel_rect);
}
