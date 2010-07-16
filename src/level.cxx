#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include <boost/algorithm/string.hpp>
#include "level.hpp"
#include "gamemgr.hpp"
#include "player.hpp"
#include "wall.hpp"

using namespace fur;

struct Level::private_state
{
  typedef std::list<SP<SquareObject> > rep_t;
  rep_t rep; //level representation is a linked list from the stl
};

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
  //boost::split(lines, whole, boost::is_any_of("\n"));

  for(int y=0;y<lines.size();y++)
    {
      string curr = lines.at(y);
      if(boost::iends_with(curr, "*"))
	{ //read line
	  for (int x=0;x<curr.size();x++)
	    {
	      if(curr.at(x) == '#')
		addObject(SP<SquareObject>(new Wall(Position(x,y))));
	      else if(curr.at(x) == '@')
		{
		  SP<Player> p = GameMgr::getInstance().getPlayer();
		  p->pos = Position(x,y);
		}
	    }
	}
    }
}

void Level::addObject(SP<SquareObject> o)
{
  private_state::rep_t::iterator it = std::find(ps->rep.begin(),ps->rep.end(),o);
  assert(it==ps->rep.end()); //assert there are no findings of this SqObj in rep

  ps->rep.push_back(o);
}

std::list<SP<SquareObject> > Level::getPos(Position p)
{
  std::list<SP<SquareObject> > result;
  for(std::list<SP<SquareObject> >::const_iterator it = ps->rep.begin();
      it != ps->rep.end();
      it++)
    if((*it)->getPosition() == p)
      result.push_back(*it);
  return result;
}

/*
{
  ifstream in ( "somefile" );
  if ( in.is_open() ) {
    string line;
    while ( getline ( in, line ) ) {
      string::size_type i = line.find_first_not_of ( " \t\n\v" );
       
      if ( i != string::npos && line[i] == '#' )
	continue;
       
      // Process non-comment line
    }
  }
}
*/
