#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include "level.hpp"
#include "gamemgr.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "enemy.hpp"
#include "objfact.hpp"
#include "libtcod.hpp"

using namespace fur;

struct Level::private_state
{
  typedef std::list<SP<SquareObject> > rep_t;
  rep_t rep; //level representation is a linked list from the stl
};

class PathCostCallback : public ITCODPathCallback {
public :
  float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData ) const
  {
    //make sure we're not asked for a path geater than one step
    assert((xFrom-xTo)*(xFrom-xTo) <= 1);
    assert((yFrom-yTo)*(yFrom-yTo) <= 1);

    //check if destination is walkable, if so, cost is always 1.0f
    //note the routine requires the end-field of the journey to be walkable,
    //even if it isn't in our game logic (player is there e.g.),
    //so double check if the next step is walkable, before moving there!
    if(Position(xTo,yTo)==to || Position(xTo,yTo)==from)
      return 1.0f;
    SP<Level> lvl = GameMgr::getInstance().getLevel();
    if(lvl->isPassable(Position(xTo,yTo)))
      return 1.0f;
    else
      return 0.0f;
  }

  PathCostCallback(Position from, Position to):from(from),to(to) {}
  Position from,to;
};

Position Level::getSize() const
{
  int max_x = 0;
  int max_y = 0;
  BOOST_FOREACH(SP<SquareObject> so, ps->rep)
    {
      const int& x = so->getPosition().x;
      const int& y = so->getPosition().y;
      max_x = std::max(max_x,x);
      max_y = std::max(max_y,y);
    }
  return Position(max_x,max_y);
}

StepResult Level::nextStepTo(Position origin, Position dest) const
{
  static StepResult stuck = StepResult(true,Position(0,0));
  //don't move to where we are already!
  assert(origin.x-dest.x != 0 || origin.y-dest.y != 0);
  SP<TCODPath> path =
    SP<TCODPath>(new TCODPath(getSize().x,
			      getSize().y,
			      new PathCostCallback(origin,dest),
			      NULL));
  
  if (!path->compute(origin.x,origin.y,dest.x,dest.y))
    return stuck; //no path available
  
  int x,y;
  if(!path->walk(&x,&y,false))
    return stuck;

  return StepResult(false,Position(x,y));
}

bool Level::isPassable(Position pos) const
{
  using boost::bind;
  std::list<SP<SquareObject> > sql = getPos(pos);
  //zero non-passible objects means the square is passable
  return 0 == std::count_if(sql.begin(),
			    sql.end(),
			    bind<bool>(pred_not(),
				       bind<bool>(pred_is_passable(),_1)));
}

Level::Level():ps(new Level::private_state)
{}

Level::~Level()
{
  delete ps;
}

void Level::fromFile(std::string file_path)
{
  using namespace std;
  ifstream inp;
  inp.open(file_path.c_str(),ios::in);

  vector<string> lines;
  while (!inp.eof())
    {
      string line;
      getline(inp,line);
      lines.push_back(line);
    }
  for(int y=0;y<lines.size();y++)
    {
      string curr = lines.at(y);
      //part of level block?
      if(boost::iends_with(curr, "*"))
	{ //read line
	  for (int x=0;x<curr.size();x++)
	    {
	      if(curr.at(x) == '#')
		addObject(SP<SquareObject>(new Wall(Position(x,y))));
	      else if(curr.at(x) == 'T')
		addObject(SP<SquareObject>(new Enemy(Position(x,y))));
	      else if(curr.at(x) == '@')
		{
		  SP<Player> p = GameMgr::getInstance().getPlayer();
		  p->pos = Position(x,y);
		}
	    }
	}
      //not part of level block
      else if (curr.size() > 0)
	{
	  vector<string> words;
	  boost::split(words, curr, boost::is_any_of("\t "));
	  vector<string> xy;
	  boost::split(xy, words.at(0), boost::is_any_of(","));
	  
	  int x = boost::lexical_cast<int>(xy.at(0));
	  int y = boost::lexical_cast<int>(xy.at(1));
	  string obj_name  = words.at(1);
	  string str_param = (words.size() > 2 ? words.at(2) : "");
	  vector<string> obj_param;
	  boost::split(obj_param,str_param,boost::is_any_of(","));

	  cerr << "(" << x << "," << y << ") : \t"
	       << obj_name << " [" << str_param << "]\n";

	  addObject(ObjFact::getInstance().build(obj_name,Position(x,y),obj_param));
	}
    }
}

void Level::addObject(SP<SquareObject> o)
{
  private_state::rep_t::iterator it = std::find(ps->rep.begin(),ps->rep.end(),o);
  assert(it==ps->rep.end()); //assert there are no findings of this SqObj in rep

  ps->rep.push_back(o);
}

std::list<SP<SquareObject> > Level::getPos(Position p) const
{
  std::list<SP<SquareObject> > result;
  for(std::list<SP<SquareObject> >::const_iterator it = ps->rep.begin();
      it != ps->rep.end();
      it++)
    if((*it)->getPosition() == p)
      result.push_back(*it);
  return result;
}
