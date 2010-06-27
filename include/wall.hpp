#ifndef __WALL_HPP
#define __WALL_HPP

#include <cassert>
#include "squareobject.hpp"

namespace fur
{
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
    void onBump(SP<Position>);
    void onEnter() {assert(false);}
    void onSquareDamaged(SP<Damage>);

    Wall(Position p):pos(p)
    {}

  private:
    Position pos;
  };
}

#endif //__WALL_HPP
