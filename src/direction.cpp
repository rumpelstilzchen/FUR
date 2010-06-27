#include "direction.hpp"

using namespace fur;

Position Direction::toPos(Position base) const
{
  switch(dir)
    {
    case  L: return Position(base.x-1,base.y  );
    case  R: return Position(base.x+1,base.y  );
    case  U: return Position(base.x  ,base.y-1);
    case  D: return Position(base.x  ,base.y+1);
    case LU: return Position(base.x-1,base.y-1);
    case LD: return Position(base.x-1,base.y+1);
    case RU: return Position(base.x+1,base.y-1);
    case RD: return Position(base.x+1,base.y+1);
    }
}
