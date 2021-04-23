#ifndef BOBSTYLE_H_INCLUDED
#define BOBSTYLE_H_INCLUDED

    #include "constants.h"
    #include "Entity.h"

    class Bobstyle : public Entity
    {
        public:

            Bobstyle(Global_variables_container* GVC);
            ~Bobstyle();

            int get_hp(); // retourne les pv de bobsytle

            void manage(); //gestion des déplacement et autre
            void display(); //afficher
            void update_tp_line();
            void dash(int instruction = BEGIN);
            void stay_in_screen(Uint32 borders);
            void lose_hp(int lost_hp);
            void reset_movements();

        private:

            Animated_sprite* m_speed_lines; //les traits qui donne une impression de chute
            Animated_sprite* m_bobstyle_thruster; //l'animation du dash
            Sprite* m_tp_line; //le sprite de la ligne de visée

            Vector m_cursor; //un vesteur qui relie le centre de bobstyle au curseur
            Vector m_tp_vector[2]; //un veecteur collinaire de m_cursor de taille fixe (avec un copie pour le reset)

            bool m_is_dashing; //vrai pendant un dash

            int m_frame_counter; //sert à connaitre à quelle frame en est le dash
            int m_hp; //les pv
            int m_dash_timer; //sert de chronomètre pour le cooldown du dash
            int m_cooldown; //temps minimal avant de pouvoir réutiliser le dash (en miliseconds)
    };

#endif // BOBSTYLE_H_INCLUDED
