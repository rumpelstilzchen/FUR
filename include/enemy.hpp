#ifndef __ENEMY_HPP
#define __ENEMY_HPP

#include "squareobject.hpp"
#include "objfact.hpp"
#include "runnable.hpp"

namespace fur
{
  class add_enemy_factory;

  class Enemy : public SquareObject, public Runnable
  {
  public:
    // inheritance
    //About (Information)
    bool isPassable() const {return false;}
    int getLightIntensity() const {return 0;}
    bool blocksLight() const {return false;}
    char getChar() const {return 'T';}
    Position getPosition() const {return pos;}

    //Events/Actions
    void onBump(Position);
    void onEnter() {assert(false);}
    void onSquareDamaged(Damage);
    void move(Position);

    //AI Routine
    void run();

    //diverse
    void playerSeenAt(Position);

    enum STATE {INNOCENT,PLAYER_SEEN};

    Enemy(Position);

  private:
    Position pos;
    STATE state;
    Position lastPlPos;
    static add_enemy_factory _f;
  };
}

#endif //__ENEMY_HPP
