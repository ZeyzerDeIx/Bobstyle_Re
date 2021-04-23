#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

    #include "constants.h"
    #include "Vector.h"

    class Hitbox
    {
        public:

            Hitbox();
            Hitbox(int center_x, int center_y, int w, int h);

            bool collision(Hitbox *other); //retourne vrai si il y à collision entre les 2 hitbox

            Vector* get_vector(int wich); //retourne le vecteur demandé

            void show(Global_variables_container* GVC);
            void update(int new_x, int new_y);
            void spin(int angle);

        private:

            int m_w;
            int m_h;
            int m_angle;

            Vector m_vectors[5][2];
    };

#endif // HITBOX_H_INCLUDED
