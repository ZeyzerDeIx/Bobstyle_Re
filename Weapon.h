#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

    #include "constants.h"
    #include "Generator.h"
    #include "Projectile.h"

    class Weapon
    {
        public:

            Weapon(Global_variables_container *GVC,
                   Entity *target, Generator *generator,
                   int relative_x,
                   int relative_y,
                   std::string image_location = "sprites/DEBUG/AnimatedDebugRect.bmp",
                   int anim_numb_phase = 9);
            ~Weapon();

            void manage();
            void display();
            void manage_and_display();
            void manage_collisions(Entity *ent); //gère les collisions entre l'arme , ses projectiles et sa cible
            void set_debug_mode(bool enable); //permet d'activer ou de désactiver le debug mode
            void update_pos(int x, int y);

            void fire();

        private:

            Global_variables_container *m_GVC;

            Entity *m_target;

            Entity *m_appearence;

            Generator *m_generator;

            Vector m_vector;

            bool m_debug_mode;

            int m_relative_pos[2];
    };

#endif // WEAPON_H_INCLUDED
