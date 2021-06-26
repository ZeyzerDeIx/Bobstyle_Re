#include "Boss_Kube.h"

using namespace std;

Kube::Kube(Global_variables_container* GVC, Entity* target, Generator *generator): Boss(GVC, target, generator, "sprites/hostile entity/boss/Kube.bmp")
{
    m_weapons.push_back(new Weapon(GVC, target, generator, -120, 80));
    m_weapons.push_back(new Weapon(GVC, target, generator, 120, 80));
}
