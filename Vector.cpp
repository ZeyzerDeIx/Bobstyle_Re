#include "Vector.h"

using namespace std;

Vector::Vector(){}

Vector::Vector(int a_x, int a_y, int b_x, int b_y)
{
    m_a[X] = floor(a_x);
    m_a[Y] = floor(a_y);
    m_b[X] = floor(b_x);
    m_b[Y] = floor(b_y);
    m_alpha = acos((m_b[Y]-m_a[Y]) / this->get_norm());
}

double Vector::get_norm()
{
    return sqrt((pow((m_b[X] - m_a[X]), 2)) + (pow((m_b[Y] - m_a[Y]), 2)));
}

double Vector::get_angle()
{
    if(m_a[X] > m_b[X])
    {
        return 180 + (180 - acos(-this->get_y()/this->get_norm()) * 180/ M_PI);
    }
    else
    {
        return acos(-this->get_y()/this->get_norm()) * 180/ M_PI;
    }
}

int Vector::get_a(int x_or_y)
{
    return m_a[x_or_y];
}

int Vector::get_b(int x_or_y)
{
    return m_b[x_or_y];
}

int Vector::get_x()
{
    return m_b[X] - m_a[X];
}

int Vector::get_y()
{
    return m_b[Y] - m_a[Y];
}

bool Vector::intersect(Vector *other)
{
    //coefficient directeur de la droite passant par ce vecteur
    double a1(0);
    if(m_b[X]-m_a[X] == 0)
    {
        a1 = INFINITE;
    }
    else
    {
        a1 = (m_b[Y]-m_a[Y]) / (m_b[X]-m_a[X]);
    }
    //coefficient directeur de la droite passant par other
    double a2(0);
    if(other->get_b(X)-other->get_a(X) == 0)
    {
        a2 = INFINITE;
    }
    else
    {
        a2 = (other->get_b(Y)-other->get_a(Y)) / (other->get_b(X)-other->get_a(X));
    }
    //ordonnée à l'origine de la droite passant par ce vecteur
    double b1 = m_a[Y] - (a1*m_a[X]);
    //ordonnée à l'origine de la droite passant par other
    double b2 = other->get_a(Y) - (a2*other->get_a(X));

    //Si les deux veteurs ne sont pas collinéaires
    if(a1 != a2)
    {
        //c'est vachement compliqué ici mais en gros ça fait intervenir des équations paramètrique de droites

        double m = -( -(m_b[X]-m_a[X])*(m_a[Y])+(m_b[X]-m_a[X])*(other->get_a(Y))+(m_b[Y]-m_a[Y])*(m_a[X])-(m_b[Y]-m_a[Y])*(other->get_a(X)) )/( (m_b[X]-m_a[X])*(other->get_b(Y)-other->get_a(Y))-(m_b[Y]-m_a[Y])*(other->get_b(X)-other->get_a(X)) );
        double k = -( (m_a[X])*(other->get_b(Y)-other->get_a(Y))-(other->get_a(X))*(other->get_b(Y)-other->get_a(Y))-(other->get_b(X)-other->get_a(X))*(m_a[Y])+(other->get_b(X)-other->get_a(X))*(other->get_a(Y)) )/( (m_b[X]-m_a[X])*(other->get_b(Y)-other->get_a(Y))-(m_b[Y]-m_a[Y])*(other->get_b(X)-other->get_a(X)) );

        if(m < 1 and m > 0 and k < 1 and k > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //si ils sont collinéaires
    else
    {
        if(b1 != b2)
        {
            return false;
        }
        else
        {
            if((m_a[X] >= other->get_a(X) and m_a[X] <= other->get_b(X)) or
               (other->get_a(X) >= m_a[X] and other->get_a(X) <= m_b[X]) or
               (m_b[X] >= other->get_a(X) and m_b[X] <= other->get_b(X)))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void Vector::set_a(int x, int y)
{
    m_a[X] = x;
    m_a[Y] = y;
}

void Vector::set_b(int x, int y)
{
    m_b[X] = x;
    m_b[Y] = y;
}

void Vector::shift(int x, int y)
{
    //déplace le vecteur selon x et y
    m_a[X] += x;
    m_a[Y] += y;
    m_b[X] += x;
    m_b[Y] += y;
}

void Vector::show_debug_line(Global_variables_container* GVC)
{
    //coefficient directeur de la droite passant par ce vecteur
    double a(0);
    //ordonnée à l'origine de la droite passant par ce vecteur
    int b(0);
    //si le déplacement en x du vecteur est nul
    if(m_b[X]-m_a[X] == 0)
    {
        //alors on rend a infini pour faire une droite verticale
        a = INFINITE;
        //et on place cette droite en x
        b = m_a[X];
    }
    else
    {
        //équation du coefficiant directeur
        a = (m_b[Y]-m_a[Y]) / (m_b[X]-m_a[X]);
        //equation de l'ordonnée à l'origine
        b = m_a[Y] - (a*m_a[X]);
    }
    //on trace la droite mais uniquement dans l'intervale correspondant au vecteur
    draw_a_line(GVC, a, b, m_a[X], m_a[Y], m_b[X], m_b[Y]);

    //on crée un foncteur kill_pixel
    Pixel_killer kill_pixel(GVC->renderer());

    //qui permet de dessiner des croix
    for(int i=-4 ; i!=5 ; i++)
    {
        //une blanche pour le point a
        kill_pixel(m_a[X]+i, m_a[Y]);
        kill_pixel(m_a[X], m_a[Y]+i);
        //une rouge pour le point b
        kill_pixel(m_b[X]+i, m_b[Y], 255, 0, 0);
        kill_pixel(m_b[X], m_b[Y]+i, 255, 0, 0);
    }
}

void Vector::spin(double angle)
{
    //on ajoute la rotation à l'angle actuel converti en radiant
    m_alpha = angle/180*M_PI;
    //si la rotation dépasse un tour complete on enleve un tour
    if(m_alpha >= 2*M_PI)
    {
        m_alpha -= 2*M_PI;
    }
    //PRIMORDIAL! On créer une sauvegarde du déplacement x du vecteur car il est modifié le premier
    double save_b_X(m_b[X]-m_a[X]);
    //on applique les équations de la rotation vectorielle dans un plan 2D
    m_b[X] = m_a[X] + (m_b[X]-m_a[X])*cos(m_alpha) - (m_b[Y]-m_a[Y])*sin(m_alpha);
    m_b[Y] = m_a[Y] + save_b_X*sin(m_alpha) + (m_b[Y]-m_a[Y])*cos(m_alpha);
}
