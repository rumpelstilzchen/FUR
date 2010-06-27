#ifndef __POSITION_HPP
#define __POSITION_HPP

namespace fur
{
  class Position
  {
  public:
    Position(int x,int y):x(x),y(y) {};
    
    int x;
    int y;
    
    bool operator==(const Position& r)
    {
      if(x==r.x && y==r.y)
	return true;
      else
	return false;
    }
    
    bool operator!=(const Position& r)
    {
      return !(*this==r);
    }
  };
}

#endif //__POSITION_HPP
