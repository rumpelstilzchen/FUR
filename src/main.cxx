#include "gamemgr.hpp"
#include "player.hpp"
#include "wall.hpp"

using namespace fur;

int main()
{
  GameMgr& gmgr = GameMgr::getInstance();
  
  /*SP<Wall> w1 = SP<Wall>(new Wall(Position(5,5)));
  SP<Wall> w2 = SP<Wall>(new Wall(Position(5,6)));
  SP<Wall> w3 = SP<Wall>(new Wall(Position(7,5)));
  SP<Wall> w4 = SP<Wall>(new Wall(Position(7,6)));

  gmgr.getLevel()->addObject(w1);
  gmgr.getLevel()->addObject(w2);
  gmgr.getLevel()->addObject(w3);
  gmgr.getLevel()->addObject(w4);
  */

  gmgr.getLevel()->fromFile("data/level_test.asc");

  gmgr.enterGameLoop();

  return 0;
}
