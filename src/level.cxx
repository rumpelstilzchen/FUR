#include <list>
#include "level.hpp"

using namespace fur;

struct Level::private_state
{
  std::list<SP<SquareObject> > rep; //level representation is a linked list from stl
};

Level::Level():ps(new Level::private_state)
{}

Level::~Level()
{
  delete ps;
}

SP<SquareObject> Level::getPos(Position p)
{
  for(std::list<SP<SquareObject> >::const_iterator it = ps->rep.begin();
      it != ps->rep.end();
      it++)
    if((*it)->getPosition() == p)
      return *it;
  return SP<SquareObject>();
}
