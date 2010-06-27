#include "libtcod.hpp"
#include "inputmgr.hpp"
#include "gamemgr.hpp"

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
    player->getPosition().x--;
  if (key.vk==TCODK_RIGHT)
    player->getPosition().x++;
  if (key.vk==TCODK_UP)
    player->getPosition().y--;
  if (key.vk==TCODK_DOWN)
    player->getPosition().y++;
  if (key.vk==TCODK_ESCAPE || key.vk==TCODK_CHAR && key.c=='Q')
    GameMgr::getInstance().setGameStatus(GameMgr::QUIT);
}
