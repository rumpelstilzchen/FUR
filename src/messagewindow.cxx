#include "messagewindow.hpp"
#include <iostream>

using namespace fur;

//maybe add another constructor
MessageWindow::MessageWindow()
{
    h=10;
    w=50;
    offscreenConsole = new TCODConsole(w,h);
    offscreenConsole->setBackgroundColor(TCODColor::black);
    offscreenConsole->clear();
}

MessageWindow::~MessageWindow()
{
    delete offscreenConsole;
}

void MessageWindow::add(Message m)
{
    if(messages.size()>=h)messages.pop_back();
    messages.push_front(m);
    clear();
    print();
    std::cerr<<"new message written: "<<m.c_str()<<messages.size()<<"\n";;

    TCODConsole::blit(offscreenConsole,0,0,w,h, TCODConsole::root,51,0,1.0f,1.0f);
}

void MessageWindow::add(std::string msg,TCOD_bkgnd_flag_t flag,const TCODColor colour)
{
    Message m(msg,flag,colour);
    add(m);
}

int MessageWindow::size()
{
    return messages.size();
}

void MessageWindow::print()
{
    int hl=h,th;
    std::list<Message>::iterator it; it = messages.begin();
    while (hl>0&&it!=messages.end()){
        th=offscreenConsole->getHeightLeftRect(0,0+h-hl,w,hl,"%s",it->c_str());
        offscreenConsole->setForegroundColor(it->getColour());
        offscreenConsole->printLeftRect(0,0+h-hl,w,hl,it->getFlag(),"%s",it->c_str());
        hl=hl-th;
        ++it;
    }
    offscreenConsole->flush();
}

void MessageWindow::clear()
{
    offscreenConsole->clear();
}

//C++ : static void blit(const TCODConsole *src,int xSrc, int ySrc, int wSrc, int hSrc, TCODConsole *dst, int xDst, int yDst, float foregroundAlpha=1.0f, float backgroundAlpha=1.0f)
