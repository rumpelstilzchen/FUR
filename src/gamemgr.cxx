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
#include "runnable.hpp"
#include "filetostrings.hpp"

using namespace fur;

boost::mt19937 gen(time(0));

struct GameMgr::private_state
{
  private_state();

  SP<TCODMap> fov_map;
  SP<Player> player;
  SP<Level> level;
  GAME_STATUS game_status;
  std::list<std::string> msgs;

  std::list<SP<Runnable> > toRun;
  int winpos_x, winpos_y;
  
  typedef std::list<std::string> LOS;
  SP<LOS> tutNames;
  SP<LOS> tutComAtt;
};

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
}

std::string slist_nth(std::list<std::string> lst,int n)
{
  std::cout << "nth: " << n << std::endl;
  typedef std::list<std::string>::iterator Iter;
  for(Iter it=lst.begin();it!=lst.end();it++,--n)
    if(n==0)
      return *it;
  assert(false);
}

std::string GameMgr::rndName()
{
  boost::uniform_int<> dist(1,getTutNames().size());
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return slist_nth(getTutNames(),die()-1);  
}

std::string GameMgr::rndAtt()
{
  boost::uniform_int<> dist(1,getTutNames().size());
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return slist_nth(getTutComAtt(),die()-1);  
}

const std::list<std::string>& GameMgr::getTutNames()
{
  return *ps->tutNames;
}

const std::list<std::string>& GameMgr::getTutComAtt()
{
  return *ps->tutComAtt;
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
  if(ps->game_status == RUNNING)
    ps->game_status = status;
}

GameMgr::GameMgr():ps(new private_state())
{
  initializeTCOD();
}

void GameMgr::render()
{
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
}

void GameMgr::enterGameLoop()
{
  // MAIN GAME LOOP
  while (ps->game_status == RUNNING && !TCODConsole::isWindowClosed())
  {
    render();
    TCODConsole::root->flush();

    //process user input
    InputMgr::getInstance().waitForInput();

    render(); //for AI
    //run Runnable object's run() fkt (e.g. for AI)
    BOOST_FOREACH(SP<Runnable> r,ps->toRun)
      {
	r->run();
      }
  }

  TCODConsole::waitForKeypress(true);  

  if(ps->game_status == WON)
    {
      TCODConsole::root->clear();
      TCODConsole::root->setForegroundColor(TCODColor::yellow);
      TCODConsole::root->printLeft(40,40,TCOD_BKGND_NONE,"SIE HABEN GEWONNEN!");
      TCODConsole::root->setForegroundColor(TCODColor::white);
      TCODConsole::root->printLeft(40,45,TCOD_BKGND_NONE,"(Tastendruck zum beenden)");
      MSG("Die Musterloesung ist geborgen.");
      MSG("Jetzt steht ihrem Abschluss...");
      MSG("nichts mehr im Wege! :-)");
      TCODConsole::root->flush();
    }
  else if(ps->game_status == LOST)
    {
      TCODConsole::root->clear();
      TCODConsole::root->setForegroundColor(TCODColor::yellow);
      TCODConsole::root->printLeft(40,40,TCOD_BKGND_NONE,"SIE HABEN VERLOREN!");
      TCODConsole::root->setForegroundColor(TCODColor::white);
      TCODConsole::root->printLeft(40,45,TCOD_BKGND_NONE,"(Tastendruck zum beenden)");
      MSG("Ausserhalb der Oeffnungszeiten des...");
      MSG("Info-Traktes wurden sie im Gebaeude gefasst!");
      MSG("Der Traum der Musterloesung ist ausgetraeumt.");
      MSG(":-(");
      MSG("");
      MSG("Aber morgen Nacht koennen sie es...");
      MSG("ja noch einmal versuchen...");
      TCODConsole::root->flush();
    }
  else
    assert(false);
  TCODConsole::waitForKeypress(true);
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
}

void GameMgr::msg(std::string m)
{
  msg(m,TCOD_BKGND_NONE,TCODColor::white); //maybe change this
}

void GameMgr::msg(std::string msg,TCOD_bkgnd_flag_t flag,const TCODColor color)
{
  if(ps->msgs.size() >= msgAreaH)
    ps->msgs.pop_front();
  ps->msgs.push_back(msg);
  TCODConsole::root->setForegroundColor(color);
  TCODConsole::root->printLeft(msgAreaX,msgAreaY + ps->msgs.size(),flag,msg.c_str());
  TCODConsole::root->flush();
}

GameMgr& GameMgr::getInstance()
{
  static GameMgr instance;
  return instance;
}
