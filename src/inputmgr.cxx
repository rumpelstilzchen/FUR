#include "libtcod.hpp"
#include "inputmgr.hpp"
#include "gamemgr.hpp"
#include "direction.hpp"

using namespace fur;

InputMgr& InputMgr::getInstance()
{
  static InputMgr instance;
  return instance;
}

void InputMgr::waitForInput() {
  SP<Player> player = GameMgr::getInstance().getPlayer();

  TCOD_key_t key=TCODConsole::waitForKeypress(true);
  if (key.vk==TCODK_LEFT)
    player->move(Direction::L);
  else if (key.vk==TCODK_RIGHT)
    player->move(Direction::R);
  else if (key.vk==TCODK_UP)
    player->move(Direction::U);
  else if (key.vk==TCODK_DOWN)
    player->move(Direction::D);
  else if (key.vk==TCODK_ESCAPE || key.vk==TCODK_CHAR && key.c=='Q')
    GameMgr::getInstance().setGameStatus(GameMgr::QUIT);
  else if (key.vk==TCODK_CHAR && key.c=='a')
    assert(false);
}
