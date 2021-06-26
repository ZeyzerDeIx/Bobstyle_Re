#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

    #include "constants.h"
    #include "Sprite.h"
    #include "Hitbox.h"
    #include "Timer.h"

    class Entity //modele de toutes les entités
    {
        public:

            Entity(Global_variables_container* GVC, std::string image_location = "sprites/DEBUG/AnimatedDebugSquare.bmp", int anim_numb_phase = 1);
            virtual ~Entity();

            virtual void set_movement(Uint32 flag_directions); //gère les déplacements

            int get_pos(int x_or_y); //retourne le coordonné demandé de la position du CENTRE de l'entité
            int get_border(int whitch_side); //retourne la coordonné du côté demandé
            int get_angle(); //retourne l'angle
            int get_damage(); //retourne les dégats que fait l'entité
            int get_speed(); //retourne la vitesse
            int get_size(int h_or_w); //renvoit la taille

            Uint32 out_of_screen(); //retourne les bords de l'écrans desquels sortent les bords de l'entitée
            Uint32 get_type(); //retourne le type de l'entitée

            //cette fonction est probablement à modifier par rapport à la nouvelle verion des sprites
            virtual bool collision(Entity *other); //renvoit vrai si il y a collision avec l'autre entité
            bool get_parameter(int which_paremeter); //retourne le paramètre demandé

            Hitbox* get_hitbox(); //retourne la hitbox de l'entité

            void set_pos(int x, int y); //change la postion du CENTRE de l'entité
            void set_parameter(int which_paremeter, bool enable); //permet de changer un paramètre
            void set_speed(int new_speed); //permet de changer la vitesse

            virtual void manage(); //gère les déplacement et autres
            virtual void display(); //affiche le sprite
            void manage_and_display(); //appel les fonction manage() et display()
            void spin(int angle); //fait tourner le sprite
            void show_debug_line(); //affiche une croix centrée sur la position de l'entité
            virtual void stay_in_screen(Uint32 borders); //remet l'entité dans l'écran
            virtual void lose_hp(int lost_hp);

        protected:

            Global_variables_container* m_GVC;

            Animated_sprite* m_sprite; //sprite de l'entité

            Hitbox m_hitbox; //hitbox de l'entité

            bool m_movement[4]; //permet de savoir vers où va l'entité
            bool m_parameters[ENTITY_PRAMAMETER_NUMBER]; /*contient plusieurs paramètres qui sont:
             * [DEBUG_MODE]: quand vrai, active le debug mode
             * [ALIVE]: vrai si l'entité est vivante
             * [IN_SCREEN]: Vrai si l'entité doit rester dans l'écran
             * [MOTION]: Vrai si l'entité peut bouger
             * [COLLISIONABLE]: Vrai si l'entité peut être collisionnée
             * [ANIMATED]: Si vrai le sprite joue son animation (si il en possède une)
             * [BOOMERANG]: SI vrai le mode boomerang du sprite est activé
             * [IS_ON_BORDER]: Vrai si l'entité touche une bordure
            */

            int m_pos[2]; //position du centre de l'entité
            int m_speed; //vitesse en pixel par second
            int m_angle; //angle de rotation de l'entité
            int m_damages; //utile uniquement pour les classes filles (debris, missile...etc)
            int m_hp; //les pv

            Timer m_timer; //sert de chronomètre

            Uint32 m_type; //sert a enregistrer le type de l'entité (entité simple, debris, missile...etc)
    };

#endif // ENTITY_H_INCLUDED
