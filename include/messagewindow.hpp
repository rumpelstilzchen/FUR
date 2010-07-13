#ifndef __MESSAGEWINDOW_H
#define __MESSAGEWINDOW_H

#include "libtcod.hpp"
#include "libtcod_int.h"
#include <list>
#include "message.hpp"

namespace fur{
class MessageWindow
{
    public:
        MessageWindow();
        virtual ~MessageWindow();
        void add(Message);
        int size();
        void print();
        void clear();
        void add(std::string msg,TCOD_bkgnd_flag_t flag,const TCODColor colour);
    protected:
    private:
        TCODConsole *offscreenConsole;
        std::list<Message> messages;
        int h;int w;
};
}
#endif // __MESSAGEWINDOW_H
