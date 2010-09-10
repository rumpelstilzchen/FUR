#ifndef __DOOR_HPP
#define __DOOR_HPP

#include <cassert>
#include "squareobject.hpp"
#include "objfact.hpp"

namespace fur
{
  class add_door_factory;

  class Door : public SquareObject
  {
  public:
    enum ORIENTATION {VERTICAL, HORIZONTAL};
    ORIENTATION orientation;
    bool isClosed;
    bool isLocked;

    // inheritance
    //About (Information)
    bool isPassable() const {return !isClosed;}
    int getLightIntensity() const {return 0;}
    bool blocksLight() const
    {
      return isClosed;
    }
    char getChar() const
    {
      if(isClosed)
	return (orientation == VERTICAL ? '|' : '-');
      else
	return '`';
    }
    Position getPosition() const {return pos;}

    //Events/Actions
    void onBump(Position);
    void onEnter();
    void onSquareDamaged(Damage);

    Door(Position p,ORIENTATION orient,bool closed,bool locked)
      :pos(p)
      ,orientation(orient)
      ,isClosed(closed)
      ,isLocked(locked)
    {}

  private:
    Position pos;
    static add_door_factory _f;
  };
}

#endif //__DOOR_HPP
