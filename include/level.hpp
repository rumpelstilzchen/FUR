#ifndef __LEVEL_HPP
#define __LEVEL_HPP

#include <util.hpp>
#include "squareobject.hpp"

namespace fur
{
  class Level
  {
  public:
    Level();
    ~Level();
    SP<SquareObject> getPos(Position);
  private:
    //we completely hide the private state to reduce unneccesary dependencies
    struct private_state;
    private_state* ps;
  };
}

#endif //__LEVEL_HPP
