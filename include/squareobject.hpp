#ifndef __SQUARE_OBJECT_HPP
#define __SQUARE_OBJECT_HPP

#include "util.hpp"
#include "position.hpp"
#include "damage.hpp"

class SquareObject
{
public:
  //About (Information)
  bool isPassable();
  int getLightIntensity();
  bool blocksLight();

  //Events/Actions
  void onBump(SP<Position>);
  void onEnter();
  void onSquareDamaged(SP<Damage>);
};

#endif //__SQUARE_OBJECT_HPP
