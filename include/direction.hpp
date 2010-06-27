#ifndef __DIRECTION_HPP
#define __DIRECTION_HPP

#include "position.hpp"

namespace fur
{
  class Direction
  {
  public:
    enum DIR {L,R,U,D,LU,LD,RU,RD};

    Direction(DIR d):dir(d) {}
    DIR dir;
    Position toPos(Position) const;
  };
}

#endif //__DIRECTION_HPP
