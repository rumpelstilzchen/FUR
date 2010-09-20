#ifndef __SOLUTION_HPP
#define __SOLUTION_HPP

#include <cassert>
#include "squareobject.hpp"
#include "objfact.hpp"
#include "door.hpp"

namespace fur
{
  class add_solution_factory;

  class Solution : public SquareObject
  {
  public:
    // inheritance
    //About (Information)
    bool isPassable() const {return false;}
    int getLightIntensity() const {return 0;}
    bool blocksLight() const {return true;}
    char getChar() const {return '%';}
    Position getPosition() const {return pos;}

    //Events/Actions
    void onBump(Position);
    void onEnter() {assert(false);}
    void onSquareDamaged(Damage);

    Solution(Position p);

  private:
    Position pos;
    static add_solution_factory _f;
  };
}

#endif //__SOLUTION_HPP
