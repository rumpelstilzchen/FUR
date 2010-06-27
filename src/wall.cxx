#include "wall.hpp"

using namespace fur;

void Wall::onBump(SP<Position> from)
{
  //here could be a terminal msg, if the player bumps into a wall
}

void Wall::onSquareDamaged(SP<Damage> dmg)
{
  //walls ignore damage for now
}
