#include "player.hpp"
#include "gamemgr.hpp"

using namespace fur;

void Player::onSquareDamaged(SP<Damage> dmg)
{
  if (dmg->type == Damage::HP_ONLY)
    {
      hitpoints-=dmg->hp_damage;
    }
}

bool Player::move(Direction d)
{
  Position newPos = d.toPos(pos);
  std::list<SP<SquareObject> > sql = GameMgr::getInstance().getLevel()->getPos(newPos);
  if(sql.size()==0)
    pos = newPos;
}
