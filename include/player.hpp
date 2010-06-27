#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <cassert>
#include "squareobject.hpp"

namespace fur
{
  class Player : SquareObject
  {
  public:
    //inheritance
    bool isPassable() const {return false;}
    int getLightIntensity() const {return 4;}
    bool blocksLight() const {return false;}
    char getChar() const {return '@';}
    Position getPosition() const {return pos;}

    void onBump(SP<Position> from) {}
    void onEnter() {assert(false);}
    void onSquareDamaged(SP<Damage>);

    //own stuff
    Player(Position p):pos(p)
    {}

    friend class InputMgr;
  private:
    Position pos;
    int hitpoints;
  };
}

#endif //__PLAYER_HPP
