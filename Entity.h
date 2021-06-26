#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

    #include "constants.h"
    #include "Sprite.h"
    #include "Hitbox.h"
    #include "Timer.h"

    class Entity //modele de toutes les entit�s
    {
        public:

            Entity(Global_variables_container* GVC, std::string image_location = "sprites/DEBUG/AnimatedDebugSquare.bmp", int anim_numb_phase = 1);
            virtual ~Entity();

            virtual void set_movement(Uint32 flag_directions); //g�re les d�placements

            int get_pos(int x_or_y); //retourne le coordonn� demand� de la position du CENTRE de l'entit�
            int get_border(int whitch_side); //retourne la coordonn� du c�t� demand�
            int get_angle(); //retourne l'angle
            int get_damage(); //retourne les d�gats que fait l'entit�
            int get_speed(); //retourne la vitesse
            int get_size(int h_or_w); //renvoit la taille

            Uint32 out_of_screen(); //retourne les bords de l'�crans desquels sortent les bords de l'entit�e
            Uint32 get_type(); //retourne le type de l'entit�e

            //cette fonction est probablement � modifier par rapport � la nouvelle verion des sprites
            virtual bool collision(Entity *other); //renvoit vrai si il y a collision avec l'autre entit�
            bool get_parameter(int which_paremeter); //retourne le param�tre demand�

            Hitbox* get_hitbox(); //retourne la hitbox de l'entit�

            void set_pos(int x, int y); //change la postion du CENTRE de l'entit�
            void set_parameter(int which_paremeter, bool enable); //permet de changer un param�tre
            void set_speed(int new_speed); //permet de changer la vitesse

            virtual void manage(); //g�re les d�placement et autres
            virtual void display(); //affiche le sprite
            void manage_and_display(); //appel les fonction manage() et display()
            void spin(int angle); //fait tourner le sprite
            void show_debug_line(); //affiche une croix centr�e sur la position de l'entit�
            virtual void stay_in_screen(Uint32 borders); //remet l'entit� dans l'�cran
            virtual void lose_hp(int lost_hp);

        protected:

            Global_variables_container* m_GVC;

            Animated_sprite* m_sprite; //sprite de l'entit�

            Hitbox m_hitbox; //hitbox de l'entit�

            bool m_movement[4]; //permet de savoir vers o� va l'entit�
            bool m_parameters[ENTITY_PRAMAMETER_NUMBER]; /*contient plusieurs param�tres qui sont:
             * [DEBUG_MODE]: quand vrai, active le debug mode
             * [ALIVE]: vrai si l'entit� est vivante
             * [IN_SCREEN]: Vrai si l'entit� doit rester dans l'�cran
             * [MOTION]: Vrai si l'entit� peut bouger
             * [COLLISIONABLE]: Vrai si l'entit� peut �tre collisionn�e
             * [ANIMATED]: Si vrai le sprite joue son animation (si il en poss�de une)
             * [BOOMERANG]: SI vrai le mode boomerang du sprite est activ�
             * [IS_ON_BORDER]: Vrai si l'entit� touche une bordure
            */

            int m_pos[2]; //position du centre de l'entit�
            int m_speed; //vitesse en pixel par second
            int m_angle; //angle de rotation de l'entit�
            int m_damages; //utile uniquement pour les classes filles (debris, missile...etc)
            int m_hp; //les pv

            Timer m_timer; //sert de chronom�tre

            Uint32 m_type; //sert a enregistrer le type de l'entit� (entit� simple, debris, missile...etc)
    };

#endif // ENTITY_H_INCLUDED
