#include "gamemgr.hpp"
#include "player.hpp"
#include "wall.hpp"

using namespace fur;

int main()
{
  GameMgr& gmgr = GameMgr::getInstance();
  
  gmgr.getLevel()->fromFile("data/level_test.asc");

  gmgr.enterGameLoop();

  return 0;
}
