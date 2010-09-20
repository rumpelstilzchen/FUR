#include <boost/lexical_cast.hpp>
#include "solution.hpp"
#include "gamemgr.hpp"

using namespace fur;

void Solution::onBump(Position from)
{
  MSG("Sieg!");
  GameMgr::getInstance().setGameStatus(GameMgr::WON);
}

void Solution::onSquareDamaged(Damage dmg)
{
  //solutions ignore damage for now
}

Solution::Solution(Position p):pos(p)
{
}

namespace fur {
  struct solution_factory : Fkt {
    SP<SquareObject> f(Position pos, std::vector<std::string> param)
    {
      return SP<SquareObject>(new Solution(pos));
    }
  };

  struct add_solution_factory
  {
    add_solution_factory()
    {
      ObjFact::getInstance().addSQType("Solution",SP<Fkt>(new solution_factory()));
    }
  };

  add_solution_factory Solution::_f = add_solution_factory();
}
