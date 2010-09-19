#ifndef __BUTTON_HPP
#define __BUTTON_HPP

#include <cassert>
#include "squareobject.hpp"
#include "objfact.hpp"
#include "door.hpp"

namespace fur
{
  class add_button_factory;

  class Button : public SquareObject
  {
  public:
    // inheritance
    //About (Information)
    bool isPassable() const {return false;}
    int getLightIntensity() const {return 0;}
    bool blocksLight() const {return true;}
    char getChar() const {return 'b';}
    Position getPosition() const {return pos;}

    //Events/Actions
    void onBump(Position);
    void onEnter() {assert(false);}
    void onSquareDamaged(Damage);

    enum OP_MODE {OPEN,CLOSE,SWITCH};

    Button(Position p, OP_MODE m, Position d);

  private:
    Position pos;
    OP_MODE mode;
    SP<Door> assoc_door;
    static add_button_factory _f;
  };
}

#endif //__BUTTON_HPP
