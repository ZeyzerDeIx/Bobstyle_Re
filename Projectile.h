#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

    #include "Entity.h"

    class Projectile: public Entity
    {
        public:

            Projectile(Global_variables_container* GVC, Entity* target, int x = 0, int y = 0, std::string image_location = "sprites/DEBUG/AnimatedDebugRect.bmp", int anim_numb_phase = 9);

            void manage(); //gérer les déplacement
            void display(); //afficher

        protected:

            int m_frame_counter; //conteur de frame

            Entity* m_target; //un pointeur vers la cible

            Vector m_vector; //un vecteur qui vise la cible

    };

#endif // PROJECTILE_H_INCLUDED
