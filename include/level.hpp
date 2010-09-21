#ifndef __LEVEL_HPP
#define __LEVEL_HPP

#include <list>
#include "util.hpp"
#include "squareobject.hpp"
#include "button.hpp"

namespace fur
{
  struct StepResult
  {
    StepResult(bool stuck, Position step)
      :stuck(stuck),step(step) {}
    bool stuck;
    Position step;
  };

  class Level
  {
  public:
    Level();
    ~Level();

    std::list<SP<SquareObject> > getPos(Position) const;
    StepResult nextStepTo(Position origin,Position dest) const;
    
    template <class T> SP<T> getTypeAt(Position,bool mustFind) const;
    template <class T> SP<T> getTypeAt(Position) const; //mustFind == false
    bool isPassable(Position) const;

    void addObject(SP<SquareObject>);
    void fromFile(std::string);

    Position getSize() const;
  private:
    //we completely hide the private state to reduce unneccesary dependencies
    struct private_state;
    SP<private_state> ps;
  };
}

#include "level_templates.hpp"

#endif //__LEVEL_HPP
