#ifndef __LEVEL_TEMPLATE_HPP
#define __LEVEL_TEMPLATE_HPP

namespace fur
{

template <class T>
SP<T> Level::getTypeAt(Position pos, bool mustFind) const
{
  typedef std::list<SP<SquareObject> > LST;
  LST lst = getPos(pos);
  for(LST::iterator it = lst.begin(); it!=lst.end(); it++)
    {
      SP<T> maybe = boost::dynamic_pointer_cast<T>(*it);
      if(maybe)
	return maybe;
    }
  if(mustFind)
    assert(false);
  else
    return SP<T>();
}

template <class T>
SP<T> Level::getTypeAt(Position pos) const
{
  return getTypeAt<T>(pos,false);
}

} // namespace

#endif //__LEVEL_TEMPLATE_HPP
