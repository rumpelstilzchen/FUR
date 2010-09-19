#include "enemy.hpp"
#include "gamemgr.hpp"
#include "level.hpp"
#include <list>
#include <string>

using namespace fur;
using std::list;
using std::string;

void Enemy::onBump(Position p)
{
}

void Enemy::onSquareDamaged(Damage d)
{
}

void Enemy::playerSeenAt(Position p)
{
  assert(pos!=p);
  if(state==INNOCENT)
    state = PLAYER_SEEN;
  lastPlPos = p;
}

Enemy::Enemy(Position p):pos(p),state(INNOCENT),lastPlPos(Position(0,0))
{
  GameMgr::getInstance().addRunnable(SP<Runnable>(this));
  
}

void Enemy::run()
{
  if(state==INNOCENT)
    return;
  if(pos==lastPlPos)
    return;

  StepResult res = GameMgr::getInstance().getLevel()->nextStepTo(pos,lastPlPos);
  if(!res.stuck)
    move(res.step);
}

void Enemy::move(Position np)
{
  if(!GameMgr::getInstance().getLevel()->isPassable(np))
    {
      SP<Player> player = GameMgr::getInstance().getLevel()->getTypeAt<Player>(np);
      if(!player)
	return;
      else
	{
	  GameMgr::getInstance().msg(name+": Haha, got ya!");
	  player->onSquareDamaged(Damage(1));
	}
    }
  pos = np;
}

namespace fur
{
  struct enemy_factory : Fkt
  {
    SP<SquareObject> f(Position pos, std::vector<std::string> param)
    {
      for(std::vector<std::string>::const_iterator it = param.begin();
	  it!=param.end();
	  it++)
	{} //don't use params at all for now
      return SP<SquareObject>(new Enemy(pos));
    }
  };

  struct add_enemy_factory
  {
    add_enemy_factory()
    {
      ObjFact::getInstance().addSQType("Enemy",SP<Fkt>(new enemy_factory()));
    }
  };

  add_enemy_factory Enemy::_f = add_enemy_factory();
} //namespace fur
