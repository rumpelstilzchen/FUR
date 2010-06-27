#include "player.hpp"

using namespace fur;

void Player::onSquareDamaged(SP<Damage> dmg)
{
  if (dmg->type == Damage::HP_ONLY)
    {
      hitpoints-=dmg->hp_damage;
    }
}
