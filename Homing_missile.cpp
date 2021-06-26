#include "Homing_missile.h"

using namespace std;

Homing_missile::Homing_missile(Global_variables_container* GVC, Entity* target, int x, int y):
    Projectile(GVC, target, x, y, "sprites/hostile entity/missiles/missile.bmp", 4)
{
    m_type = HOMING_MISSILE; //type: missile guidé

    m_sprite->set_anim_speed(4); //la vitesse d'animation

    m_damages = 5; //les dégats (équivalent à deux coeurs)
}
