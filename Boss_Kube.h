#ifndef BOSS_KUBE_H_INCLUDED
#define BOSS_KUBE_H_INCLUDED

    #include "constants.h"
    #include "Boss.h"

    class Kube: public Boss
    {
        public:

            Kube(Global_variables_container* GVC, Entity* target, Generator *generator);

        private:

    };

#endif // BOSS_KUBE_H_INCLUDED
