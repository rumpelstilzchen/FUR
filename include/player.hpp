#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <cassert>
#include "squareobject.hpp"
#include "direction.hpp"
#include "level.hpp"

namespace fur
{
  class Player : public SquareObject
  {
  public:
    //inheritance
    bool isPassable() const {return false;}
    int getLightIntensity() const {return 4;}
    bool blocksLight() const {return false;}
    char getChar() const {return '@';}
    Position getPosition() const {return pos;}
    void move(Direction);

    void onBump(Position from) {}
    void onEnter() {assert(false);}
    void onSquareDamaged(Damage);

    //own stuff
    Player(Position p):pos(p),hitpoints(10)
    {}

    friend class InputMgr;
    friend class Level;
  private:
    Position pos;
    int hitpoints;


  };
}

#endif //__PLAYER_HPP
