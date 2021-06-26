#ifndef HOMING_MISSILE_H_INCLUDED
#define HOMING_MISSILE_H_INCLUDED

    #include "Projectile.h"

    class Homing_missile: public Projectile
    {
        public:

            Homing_missile(Global_variables_container* GVC, Entity* target, int x = 0, int y = 0);

    };

#endif // HOMING_MISSILE_H_INCLUDED
