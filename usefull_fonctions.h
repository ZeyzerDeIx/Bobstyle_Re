#ifndef USEFULL_FONCTIONS_H_INCLUDED
#define USEFULL_FONCTIONS_H_INCLUDED

    #include "constants.h"
    #include "Global_variables_container.h"
    #include "Sprite.h"
    #include "input_alpha_translation.h"

    class Sprite;

    //demarre la SDL en pleine écran et retourne ce dernier
    Global_variables_container* start_SDL();

    //enregistre une capture d'écran
    void save_screenshot(Global_variables_container* const GVC);

    //sauvgarde le nom et le score d'un joueur
    void save(std::string const name, int const score);

    //trace une droite d'équation y = ax + b
    void draw_a_line(Global_variables_container* GVC, double a, int b);
    //la droite devient un segment
    void draw_a_line(Global_variables_container* GVC, double a, int b, int a_x, int a_y, int b_x, int b_y);

    //affiche un rectangle noir cerné de gris
    void draw_box(Global_variables_container* GVC, int w, int h, int border_width);

    //renvoit un sprite qui est une capture d'écran
    Sprite* screenshot(Global_variables_container* GVC, int alpha = 0);

    //renvoit une surface sur mesure
    SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display);

    //transforme les int en string
    std::string int_to_string(int number);

    //permet au joueur de saisir un mot
    std::string enter_text(Global_variables_container* GVC, std::string prevent_text = "Entrez votre nom");

    //trie les scores et les renvoit sous forme d'une chaîne de caractère intérprétable
    std::string sort_scores(std::map<std::string, int> scores_table);

    //transforme les strings en int
    int string_to_int(std::string number);

    //renvoit une taile de débris avec une répartition aménagée
    int debris_rand();

    //renvoit une map avec comme clés les noms des joueurs associés à leur scores (nom = first et score = second)
    std::map<std::string, int> get_saved_scores();

    //foncteur permettant d'activer et descativer le plein écran
    class Pixel_killer
    {
        public:
            Pixel_killer(SDL_Renderer* renderer);
            //met le pixel de coordonnées x,y dans la couleur demandée (en blanc par defaut)
            void operator()(int x, int y, int R = 255, int G = 255, int B = 255);
        private:
            SDL_Renderer* m_renderer;
            SDL_Rect m_pixel_rect;
    };

#endif // USEFULL_FONCTIONS_H_INCLUDED
