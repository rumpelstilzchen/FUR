#ifndef __UTIL_HPP
#define __UTIL_HPP

#include <cassert>
#include <boost/shared_ptr.hpp>

#define SP boost::shared_ptr

namespace fur
{
  struct pred_not
  {
    bool operator()(bool b)
    {
      return !b;
    }
  };
}

#endif //UTIL_HPP
