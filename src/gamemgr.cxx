#include <list>
#include <algorithm>
#include <ctime>
#include <boost/foreach.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include "constants.hpp"
#include "gamemgr.hpp"
#include "libtcod.hpp"
#include "squareobject.hpp"
#include "player.hpp"
#include "level.hpp"
#include "enemy.hpp"
#include "inputmgr.hpp"
#include "message.hpp"
#include "messagewindow.hpp"
#include "runnable.hpp"
#include "filetostrings.hpp"

using namespace fur;

boost::mt19937 gen;

struct GameMgr::private_state
{
  private_state();

  SP<TCODMap> fov_map;
  SP<Player> player;
  SP<Level> level;
  GAME_STATUS game_status;

  std::list<SP<Runnable> > toRun;
  int winpos_x, winpos_y;
  
  typedef std::list<std::string> LOS;
  SP<LOS> tutNames;
  SP<LOS> tutComAtt;
  SP<LOS> tutComHit;
};

std::string slist_nth(std::list<std::string> lst,int n)
{
  typedef std::list<std::string>::iterator Iter;
  for(Iter it=lst.begin();it!=lst.end();it++,--n)
    if(n==0)
      return *it;
  assert(false);
}

GameMgr::private_state::private_state()
    :fov_map(SP<TCODMap>(new TCODMap (mapSizeX,mapSizeY)))
    ,player(SP<Player>(new Player(Position(1,1))))
    ,level(SP<Level>(new Level))
    ,game_status(RUNNING)
    ,winpos_x(0)
    ,winpos_y(0)
{
  level->addObject(player);
  
  tutNames = SP<LOS>(new LOS(FileToStrings("data/tut_names.txt")));
  tutComAtt = SP<LOS>(new LOS(FileToStrings("data/tut_att.txt")));
  tutComHit = SP<LOS>(new LOS(FileToStrings("data/tut_hit.txt")));
}

std::string GameMgr::rndName()
{
  boost::uniform_int<> dist(1,getTutNames().size());
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return slist_nth(getTutNames(),die());  
}

std::string GameMgr::rndAtt()
{
  boost::uniform_int<> dist(1,getTutNames().size());
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return slist_nth(getTutComAtt(),die());  
}

std::string GameMgr::rndHit()
{
  boost::uniform_int<> dist(1,getTutNames().size());
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return slist_nth(getTutComHit(),die());  
}

const std::list<std::string>& GameMgr::getTutNames()
{
  return *ps->tutNames;
}

const std::list<std::string>& GameMgr::getTutComAtt()
{
  return *ps->tutComAtt;
}

const std::list<std::string>& GameMgr::getTutComHit()
{
  return *ps->tutComHit;
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

void GameMgr::addRunnable(SP<Runnable> r)
{
  assert(0 == count(ps->toRun.begin(),ps->toRun.end(),r));
  ps->toRun.push_back(r);
}

void GameMgr::remRunnable(SP<Runnable> r)
{
  assert(1 == count(ps->toRun.begin(),ps->toRun.end(),r));
  ps->toRun.remove(r);
}

void GameMgr::setGameStatus(GAME_STATUS status)
{
  ps->game_status = status;
}

GameMgr::GameMgr():ps(new private_state)
{
  cnt=0; //delete this
  initializeTCOD();
}

void GameMgr::enterGameLoop()
{
  // MAIN GAME LOOP
  while (ps->game_status == RUNNING && !TCODConsole::isWindowClosed())
  {
    //run Runnable object's run() fkt (e.g. for AI)
    BOOST_FOREACH(SP<Runnable> r,ps->toRun)
      {
	r->run();
      }

    //build FOV MAP
    for (int i=0;i<playAreaX;i++)
      for (int j=0;j<playAreaY;j++)
      {
        std::list<SP<SquareObject> > sql = ps->level->getPos(Position(i,j));
        int light_blockers = std::count_if(sql.begin(),sql.end(),pred_blocks_light());
        if (light_blockers>0)
          ps->fov_map->setProperties(i,j,false,true);
        else
          ps->fov_map->setProperties(i,j,true,true);
      }

    //compute FOV around player
    ps->fov_map->computeFov(ps->player->getPosition().x,ps->player->getPosition().y);

    //render based on FOV
    for (int x=0;x<playAreaX;x++)
      for (int y=0;y<playAreaY;y++)
      {
        //x,y   are the positions on the screen
        //px,py are the positions on the map
        int px = ps->winpos_x+x;
        int py = ps->winpos_y+y;
        if (ps->fov_map->isInFov(px,py))
        {
          std::list<SP<SquareObject> > sql = ps->level->getPos(Position(px,py));
          if (sql.size()>0)
          {
            SP<SquareObject> sq = sql.front();
            TCODConsole::root->setChar(x,y,sq->getChar());

	    //are there enemys seen? if so, they see you too... ;-) 
	    SP<Enemy> enemy = ps->level->getTypeAt<Enemy>(Position(px,py));
	    if(enemy)
	      enemy->playerSeenAt(Position(ps->player->getPosition().x
					   ,ps->player->getPosition().y));
	  }
          else
            TCODConsole::root->setChar(x,y,'.');
        }
        else
          TCODConsole::root->setChar(x,y,' '); //invisible field (out of FOV)
      }

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

void GameMgr::msg(std::string m)
{
  msg(m,TCOD_BKGND_NONE,TCODColor::white); //maybe change this
}

void GameMgr::msg(std::string msg,TCOD_bkgnd_flag_t flag,const TCODColor color)
{
  if(msgs.size() >= msgAreaH)
    msgs.pop_front();
  msgs.push_back(msg);
  TCODConsole::root->setForegroundColor(color);
  TCODConsole::root->printLeft(msgAreaX,msgAreaY + msgs.size(),flag,msg.c_str());
}

GameMgr& GameMgr::getInstance()
{
  static GameMgr instance;
  return instance;
}
