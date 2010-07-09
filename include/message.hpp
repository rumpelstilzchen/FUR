#ifndef __MESSAGE_HPP
#define __MESSAGE_HPP

#include <string>
#include "libtcod.hpp"
#include "libtcod_int.h"

namespace fur{

class Message
{
private:
  std::string msg;
  TCOD_bkgnd_flag_t flag;
  TCODColor colour;
public:
  Message();
  Message(std::string);
  Message(std::string s,TCOD_bkgnd_flag_t flag,TCODColor c);
  ~Message();

  const char*c_str();
  TCOD_bkgnd_flag_t getFlag();
  TCODColor getColour();
};

}
#endif //MESSAGE_HPP
