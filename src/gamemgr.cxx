#include "constants.hpp"
#include "gamemgr.hpp"
#include "libtcod.hpp"
#include "squareobject.hpp"
#include "player.hpp"
#include "level.hpp"
#include "inputmgr.hpp"

using namespace fur;

struct GameMgr::private_state
{
  SP<TCODMap> fov_map;
  SP<Player> player;
  SP<Level> level;
  GAME_STATUS game_status;

  private_state();
};

GameMgr::private_state::private_state()
  :fov_map(SP<TCODMap>(new TCODMap (mapSizeX,mapSizeY))),
   player(SP<Player>(new Player(Position(1,1)))),
   level(SP<Level>(new Level)),
   game_status(RUNNING)
{}

void initializeTCOD()
{
  // initialize terminal window
  TCODConsole::initRoot(winSizeX,winSizeY,"FUR",false);
  TCODConsole::root->setForegroundColor(TCODColor::lightBlue);
  TCODConsole::root->setBackgroundColor(TCODColor::black);
  TCODMouse::showCursor(false);
  TCODConsole::root->clear();
}

void GameMgr::setGameStatus(GAME_STATUS status)
{
  ps->game_status = status;
}

GameMgr::GameMgr():ps(new private_state)
{
  initializeTCOD();
  
  //initialize FOV MAP
  for (int i=0;i<50;i++)
    for (int j=0;j<50;j++)
      ps->fov_map->setProperties(i,j,true,true);
}

void GameMgr::enterGameLoop()
{
  // MAIN GAME LOOP
  while (ps->game_status == RUNNING && !TCODConsole::isWindowClosed())
    {
      //compute FOV around player
      ps->fov_map->computeFov(ps->player->getPosition().x,ps->player->getPosition().y);

      //render everything visible on window
      for (int x=0;x<winSizeX;x++)
	for (int y=0;y<winSizeY;y++)
	  if (ps->fov_map->isInFov(x,y))
	    {
	      SP<SquareObject> sq = ps->level->getPos(Position(x,y));
	      if(sq)
		TCODConsole::root->setChar(x,y,sq->getChar());
	      else
		TCODConsole::root->setChar(x,y,'.');
	    }
	  else
	    TCODConsole::root->setChar(x,y,' '); //nothing to see here

      //draw everything
      TCODConsole::root->flush();

      //process user input
      InputMgr::getInstance().waitForInput();
    }
}

SP<Player> GameMgr::getPlayer() const
{
  return ps->player;
}

GameMgr::~GameMgr()
{
  delete ps;
}

GameMgr& GameMgr::getInstance()
{
  static GameMgr instance;
  return instance;
}
