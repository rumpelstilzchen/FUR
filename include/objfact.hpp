#ifndef __OBJFACT_HPP
#define __OBJFACT_HPP

#include <string>
#include <vector>
#include <map>
#include <cassert>
#include "squareobject.hpp"
#include "util.hpp"
#include "position.hpp"

namespace fur
{
  struct Fkt {
    virtual SP<SquareObject> f(Position pos, std::vector<std::string> param) = 0;
  };

  class ObjFact
  {
  private: 
    //singleton foo
    ObjFact() {}
    ~ObjFact() {} 
    ObjFact(const ObjFact &);             // intentionally undefined
    ObjFact & operator=(const ObjFact &); // intentionally undefined
  
    std::map<std::string,SP<Fkt> > factories;

  public:
    void addSQType(std::string name, SP<Fkt> factory);

    SP<SquareObject> build(std::string name,
			   Position pos,
			   std::vector<std::string> param);

    //singleton foo
    static ObjFact &getInstance();
  };
}

#endif //__OBJFSCT_HPP
