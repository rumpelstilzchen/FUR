#include "message.hpp"
#include <string>

using namespace fur;
//fur::Message::Message(std::string& s,TCOD_bkgnd_flag_t f,const TCODColor c)
Message::Message()
{
  msg="";
}

Message::Message(std::string x)
{
  msg=x;
  flag=TCOD_BKGND_NONE;
  colour=TCODColor::white;
}

Message::Message(std::string s,TCOD_bkgnd_flag_t f,TCODColor c)
{
     flag=f;
     msg=s;
     colour=c;
}

Message::~Message()
{

}

const char*Message::c_str()
{
    return msg.c_str();
}

TCOD_bkgnd_flag_t Message::getFlag()
{
    return flag;
}

TCODColor Message::getColour()
{
    return colour;
}
