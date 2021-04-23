#ifndef DEBRIS_H_INCLUDED
#define DEBRIS_H_INCLUDED

    #include "constants.h"
    #include "Entity.h"

    class Debris: public Entity
    {
        public:

            Debris(Global_variables_container* GVC, int dimension);

        private:

            int m_dimension;
    };

#endif // DEBRIS_H_INCLUDED
