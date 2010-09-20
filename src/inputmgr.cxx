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
  else if (key.vk==TCODK_CHAR && key.c=='c')
    {
      MSG("Tuer schliessen: Geben sie nun eine Richtung an: ");
      TCOD_key_t dir_key = TCODConsole::waitForKeypress(true);
      Direction::DIR dir;
      if (dir_key.vk==TCODK_LEFT)
	dir = Direction::L;
      else if (dir_key.vk==TCODK_RIGHT)
	dir = Direction::R;
      else if (dir_key.vk==TCODK_UP)
	dir = Direction::U;
      else if (dir_key.vk==TCODK_DOWN)
	dir = Direction::D;
      else
	{
	  MSG(" -> ungueltige Richtung");
	  return;
	}
      Position door_pos = Direction(dir).toPos(player->getPosition());
      SP<Door> door = GameMgr::getInstance().getLevel()->getTypeAt<Door>(door_pos);
      if(door)
	{
	  door->isClosed=true;
	  MSG(" -> Tuer geschlossen.");
	}
      else
	MSG(" -> keine Tuer gefunden.");
    }
  else if (key.vk==TCODK_ESCAPE || key.vk==TCODK_CHAR && key.c=='Q')
    GameMgr::getInstance().setGameStatus(GameMgr::QUIT);
}
