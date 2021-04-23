#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

    #include "constants.h"
    #include "usefull_fonctions.h"

    class Vector
    {
        public:
            Vector(); //constructeur vide
            Vector(int a_x, int a_y, int b_x, int b_y);

            double get_norm(); //retourne la norme du vecteur
            double get_angle(); //retourne l'angle par rapport à l'axe y

            int get_a(int x_or_y);
            int get_b(int x_or_y);
            int get_x();
            int get_y();

            bool intersect(Vector *other); //retourne vrai si ce vecteur croise other (INCOMPLETE!)

            void set_a(int x, int y);
            void set_b(int x, int y);
            void shift(int x, int y); //déplace le vecteur selon x et y
            void show_debug_line(Global_variables_container* GVC); //affiche le vecteur
            void spin(double angle); //fait tourner le vecteur vers la gauche (angle en °)
        private:
            double m_a[2];
            double m_b[2];
            double m_alpha; //alpha est l'angle par rapport à l'axe y
    };

#endif // VECTOR_H_INCLUDED
