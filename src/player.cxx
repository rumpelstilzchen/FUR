#include <algorithm>
#include <boost/foreach.hpp>
#include "util.hpp"
#include "player.hpp"
#include "gamemgr.hpp"
#include <iostream>

using namespace fur;

void Player::onSquareDamaged(Damage dmg)
{
  MSG("Sie wurden erwischt, verloren..");
  GameMgr::getInstance().setGameStatus(GameMgr::LOST);
}

void Player::move(Direction d)
{
  Position newPos = d.toPos(pos);
  std::list<SP<SquareObject> > sql = GameMgr::getInstance().getLevel()->getPos(newPos);

  bool is_passable = 
    GameMgr::getInstance().getInstance().getLevel()->isPassable(newPos);

  BOOST_FOREACH(SP<SquareObject> so, sql) //bump
    {
      so->onBump(pos);
    }

  if(is_passable)
    {
      BOOST_FOREACH(SP<SquareObject> so, sql) //enter
	{
	  so->onEnter();
	}
      pos = newPos;
    }
}
