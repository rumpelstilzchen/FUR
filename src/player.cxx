#include <algorithm>
#include <boost/bind.hpp>
#include "util.hpp"
#include "player.hpp"
#include "gamemgr.hpp"
#include <iostream>

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
  using boost::bind;
  Position newPos = d.toPos(pos);
  std::list<SP<SquareObject> > sql = GameMgr::getInstance().getLevel()->getPos(newPos);

  int not_passible = std::count_if(sql.begin(),
				   sql.end(),
				   bind<bool>(pred_not(),
					      bind<bool>(pred_is_passable(),_1)));
  if(not_passible==0) // all objects in square are passable
    pos = newPos;     // so we can move our player in
}
