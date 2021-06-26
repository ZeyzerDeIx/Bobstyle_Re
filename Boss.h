#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

    #include "constants.h"
    #include "Entity.h"
    #include "Weapon.h"

    class Boss: public Entity
    {
        public:

            Boss(Global_variables_container* GVC,
                 Entity* target,
                 Generator *generator,
                 std::string image_location = "sprites/DEBUG/DEBUG_BOSS.bmp",
                 int anim_numb_phase = 1);
            virtual ~Boss();

            void manage();
            void display();

        protected:

            int m_hp_max; //pv max du boss

            std::vector<Weapon*> m_weapons; //les armes du boss

            Entity *m_target;

    };

#endif // BOSS_H_INCLUDED
