#ifndef __SQUARE_OBJECT_HPP
#define __SQUARE_OBJECT_HPP

#include "util.hpp"
#include "position.hpp"
#include "damage.hpp"

namespace fur
{
  class SquareObject
  {
  public:
    //About (Information)
    virtual bool isPassable() const = 0;
    virtual int getLightIntensity() const = 0;
    virtual bool blocksLight() const = 0;
    virtual char getChar() const = 0;
    virtual Position getPosition() const = 0;

    //Events/Actions
    virtual void onBump(SP<Position>) = 0;
    virtual void onEnter() = 0;
    virtual void onSquareDamaged(SP<Damage>) = 0;

    virtual ~SquareObject(){}
  };

  struct pred_blocks_light {
    bool operator()(SP<SquareObject> s) {
      return s->blocksLight();
    }
  };

  struct pred_is_passable {
    bool operator()(SP<SquareObject> s) {
      return s->isPassable();
    }
  };
}

#endif //__SQUARE_OBJECT_HPP
