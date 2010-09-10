#include "objfact.hpp"

namespace fur
{
  void ObjFact::addSQType(std::string name, SP<Fkt> factory)
  {
    factories[name] = factory;
  }

  SP<SquareObject> ObjFact::build(std::string name,
				  Position pos,
				  std::vector<std::string> param)
  {
    SP<Fkt> fkt = factories[name];
    assert(fkt);
    return fkt->f(pos,param);
  }

  //singleton stuff
  ObjFact& ObjFact::getInstance()
  {
    static ObjFact instance;
    return instance;
  }
}

