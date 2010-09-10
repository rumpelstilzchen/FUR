#include "wall.hpp"

using namespace fur;

void Wall::onBump(Position from)
{
  //here could be a terminal msg, if the player bumps into a wall
}

void Wall::onSquareDamaged(Damage dmg)
{
  //walls ignore damage for now
}

namespace fur {
  struct wall_factory : Fkt {
    SP<SquareObject> f(Position pos, std::vector<std::string> param) {
      return SP<SquareObject>(new Wall(pos));
    }
  };

  struct add_wall_factory
  {
    add_wall_factory()
    {
      ObjFact::getInstance().addSQType("Wall",SP<Fkt>(new wall_factory()));
    }
  };

  add_wall_factory Wall::_f = add_wall_factory();
}
