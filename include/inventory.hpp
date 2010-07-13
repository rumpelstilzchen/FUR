#ifndef __INVENTORY_HPP
#define __INVENTORY_HPP
/*
  this file should specify the inventory of a player
  including an extra window who contains the inventory
  25x50 should be enough (50 rows of length 25)
*/

#include <list>
#include "carryableitem.hpp"
#include "libtcod.hpp"
#include "libtcod_int.h"

namespace fur {
class Inventory
{
private:
  std::list<CarryAbleItem> items;
  TCODConsole *offscreenConsole;
public:
  void openinventorywindow();
  void closeinventorywindow(); //no error code handling, change this??
  Inventory();
  ~Inventory();
};
}

#endif //__INVENTORY_HPP
