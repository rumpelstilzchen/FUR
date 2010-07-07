#include <list>
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

  int winpos_x, winpos_y;

  private_state();
};

GameMgr::private_state::private_state()
  :fov_map(SP<TCODMap>(new TCODMap (mapSizeX,mapSizeY))),
   player(SP<Player>(new Player(Position(1,1)))),
   level(SP<Level>(new Level)),
   game_status(RUNNING),
   winpos_x(0),
   winpos_y(0)
{
  level->addObject(player);
}

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
}

void GameMgr::enterGameLoop()
{
  // MAIN GAME LOOP
  while (ps->game_status == RUNNING && !TCODConsole::isWindowClosed())
    {
      //build FOV MAP
      for (int i=0;i<playAreaX;i++)
	for (int j=0;j<playAreaY;j++)
	  {
	    SP<SquareObject> sq = ps->level->getPos(Position(i,j)).front(); //TODO
	      if(sq)
	        if(sq->blocksLight())
		  {
		    ps->fov_map->setProperties(i,j,false,true);
		    continue;
		  }
	      ps->fov_map->setProperties(i,j,true,true);
	  }

      //compute FOV around player
      ps->fov_map->computeFov(ps->player->getPosition().x,ps->player->getPosition().y);

      //render based on FOV
      for (int x=0;x<winSizeX;x++)
	for (int y=0;y<winSizeY;y++)
	  {
	    //x,y   are the positions on the screen
	    //px,py are the positions on the map
	    int px = ps->winpos_x+x;
	    int py = ps->winpos_y+y;
	    if (ps->fov_map->isInFov(px,py))
	      {
		std::list<SP<SquareObject> > sql = ps->level->getPos(Position(px,py));
		if(sql.size()>0)
		  {
		    SP<SquareObject> sq = sql.front();
		    TCODConsole::root->setChar(x,y,sq->getChar());
		}
		else
		  TCODConsole::root->setChar(x,y,'.');
	    }
	    else
	      TCODConsole::root->setChar(x,y,' '); //invisible field (out of FOV)
	  }

      //draw everything
      msg("Draw funktioniert");
      TCODConsole::root->flush();

      //process user input
      InputMgr::getInstance().waitForInput();
    }
}

SP<Player> GameMgr::getPlayer() const
{
  return ps->player;
}

SP<Level> GameMgr::getLevel() const
{
  return ps->level;
}

GameMgr::~GameMgr()
{
  delete ps;
}

void GameMgr::msg(std::string msg) {

  currentString=msg;

  char*cstr=new char[currentString.size()+1];

  strcpy (cstr, currentString.c_str());

  TCODConsole::root->printLeft(msgAreaX, msgAreaY, TCOD_BKGND_NONE, "test");

  delete[]cstr;
  //add msg to console
}

GameMgr& GameMgr::getInstance()
{
  static GameMgr instance;
  return instance;
}
