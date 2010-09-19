#include "door.hpp"

using namespace fur;

void Door::onBump(Position from)
{
  if(!isLocked)
    isClosed = false;
}

void Door::onEnter()
{
}

void Door::onSquareDamaged(Damage dmg)
{
  //doors ignore damage for now
}

namespace fur {
  struct door_factory : Fkt {
    SP<SquareObject> f(Position pos, std::vector<std::string> param) {
      Door::ORIENTATION o = Door::VERTICAL;
      bool closed = true;
      bool locked = false;
      for(std::vector<std::string>::const_iterator it = param.begin(); it!=param.end(); it++)
	{
	  if((*it)=="horizontal")
	    o=Door::HORIZONTAL;
	  else if ((*it)=="vertical")
	    o=Door::VERTICAL;
	  else if ((*it)=="open")
	    closed = false;
	  else if ((*it)=="closed")
	    closed = true;
	  else if ((*it)=="locked")
	    locked = true;
	}
      return SP<SquareObject>(new Door(pos,o,closed,locked));
    }
  };

  struct add_door_factory
  {
    add_door_factory()
    {
      ObjFact::getInstance().addSQType("Door",SP<Fkt>(new door_factory()));
    }
  };

  add_door_factory Door::_f = add_door_factory();
}
