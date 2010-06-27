#include "gamemgr.hpp"
#include "player.hpp"

int main()
{
  fur::GameMgr& gmgr = fur::GameMgr::getInstance();
  gmgr.enterGameLoop();

  return 0;
}
