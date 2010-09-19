#include <boost/lexical_cast.hpp>
#include "button.hpp"
#include "gamemgr.hpp"

using namespace fur;

void Button::onBump(Position from)
{
  if(assoc_door->isClosed)
    {
     if(mode==SWITCH || mode==OPEN)
       assoc_door->isClosed = false;
    }
  else if(mode==SWITCH || mode==CLOSE)
    assoc_door->isClosed = true;
}

void Button::onSquareDamaged(Damage dmg)
{
  //buttons ignore damage for now
}

Button::Button(Position p, OP_MODE m, Position d):pos(p),mode(m)
{
  assoc_door = GameMgr::getInstance().getLevel()->getTypeAt<Door>(d,true);
}

namespace fur {
  struct button_factory : Fkt {
    SP<SquareObject> f(Position pos, std::vector<std::string> param)
    {
      Button::OP_MODE m;
      if(param.at(0) == "open")
	m=Button::OPEN;
      else if (param.at(0) == "close")
	m=Button::CLOSE;
      else if (param.at(0) == "switch")
	m=Button::SWITCH;
      else
	assert(false);

      int x = boost::lexical_cast<int>(param.at(1));
      int y = boost::lexical_cast<int>(param.at(2));

      Position d(x,y);

      return SP<SquareObject>(new Button(pos,m,d));
    }
  };

  struct add_button_factory
  {
    add_button_factory()
    {
      ObjFact::getInstance().addSQType("Button",SP<Fkt>(new button_factory()));
    }
  };

  add_button_factory Button::_f = add_button_factory();
}
