#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

    #include "constants.h"
    #include "usefull_fonctions.h"
    #include "Global_variables_container.h"

    class  Sprite
    {
        public:

            Sprite();
            Sprite(Global_variables_container* GVC);
            Sprite(Global_variables_container* GVC, SDL_Surface* image);
            Sprite(Global_variables_container* GVC, std::string image_location);
            virtual ~Sprite();

            Sprite* self_copy();

            void load_new_surface(SDL_Surface* new_image); //permet de changer manuelement l'image

            void reset_image(); //remet l'image dans son état d'origine

            virtual bool presence_of_bugs();

            virtual int get_border(int wich_side); //retourne la coordonné du côté demandé
            virtual int get_pos(int x_or_y); //retourne le coordonné demandé de la position du CENTRE du Sprite
            virtual int get_size(int h_or_w); //retourne la largeur ou la hauteur selon la demande

            virtual SDL_Surface* get_original_image(); //retourne un pointeur vers la surface originale du Sprite

            virtual void set_pos(int x, int y); //change la postion du CENTRE du Sprite
            virtual void set_debug_mode(bool debug_mode); //active ou desactive le mode debug
            virtual void display(); //affiche le Sprite sur l'écran
            virtual void spin(int angle); //fait pivoter le Sprite vers la gauche avec l'angle demandé
            virtual void reset_angle(); //remet l'angle à 0

        protected:

            Global_variables_container* m_GVC; //pointeur vers le GVC
            SDL_Texture* m_image; //image à afficher du Sprite, modifiable
            SDL_Surface* m_original_image; //image d'origine du Sprite, non modifiable

            bool m_debug_mode; //quand vrai, active le debug mode

            int m_pos[2]; //position du CENTRE du Sprite
            int m_angle; //degrés de rotation actuel vers la gauche
    };


    class Animated_sprite: public Sprite
    {
        public:

            Animated_sprite();
            Animated_sprite(Global_variables_container* GVC, std::string image_location, int number_of_phase);
            ~Animated_sprite();

            int get_pos(int x_or_y); //retourne le coordonné demandé de la position du CENTRE du Sprite
            int get_border(int witch_side); //retourne la coordonné du côté demandé
            int get_size(int h_or_w); //retourne la largeur ou la hauteur selon la demande

            bool presence_of_bugs();

            Sprite* operator[](int key);

            void set_debug_mode(bool debug_mode); //active ou desactive le mode debug
            void set_pos(int x, int y); //change la postion du CENTRE des Sprite
            void set_animation(bool enable); //permet d'activer ou de désactiver l'animation
            void set_anim_speed(int speed); //permet de choisir la vitesse d'animation en sprite/frame
            void reset_animation(); //remet l'animation au point de départ
            void reset_angle(); //remet l'angle des phases à 0

            void enable_boomrang_mode(); //fait passer l'animation en mode boomrang/mirroir
            void manage(); //gerer l'animation
            void display(); //affiche le Sprite sur l'écran
            void spin(int angle); //fait pivoter les Sprite vers la gauche avec l'angle demandé
            void skip_phase(int number);

        protected:

            int m_number_of_phase; //nombre d'images
            int m_animation_speed; //vistesse de défilement des image en sprite/frame
            int m_current; //indique la phase actuelle de l'animation
            int m_frame_counter; //sert à conter les frame pour gerer la vitesse d'anmation

            bool m_animation_enable; //vrai si l'animation doit être jouée

            std::vector<Sprite*> m_phases; //tableau de toutes les phases de l'animation
    };

#endif // SPRITE_H_INCLUDED
