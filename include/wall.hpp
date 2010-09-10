#ifndef __WALL_HPP
#define __WALL_HPP

#include <cassert>
#include "squareobject.hpp"
#include "objfact.hpp"

namespace fur
{
  class add_wall_factory;

  class Wall : public SquareObject
  {
  public:
    // inheritance
    //About (Information)
    bool isPassable() const {return false;}
    int getLightIntensity() const {return 0;}
    bool blocksLight() const {return true;}
    char getChar() const {return '#';}
    Position getPosition() const {return pos;}

    //Events/Actions
    void onBump(Position);
    void onEnter() {assert(false);}
    void onSquareDamaged(Damage);

    Wall(Position p):pos(p)
    {}

  private:
    Position pos;
    static add_wall_factory _f;
  };
}

#endif //__WALL_HPP
