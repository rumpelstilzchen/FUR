#include <iostream>
#include "libtcod.hpp"
#include "squareobject.hpp"

using namespace std;

int main()
{
    TCODConsole::initRoot(80,50,"FUR",false);
    TCODMap*m = new TCODMap (100, 100);
    //    m->setProperties (5,5,true,false);

    {
      int x = 5, y = 8;
      TCODLine::init(x,y,13,4);
      do {
	m->setProperties (x,y,true,false);
      } while (!TCODLine::step(&x,&y));
    }
    
    int endGame=0;

    //    const char *font="terminal.png";
    TCODConsole::root->setForegroundColor(TCODColor::lightBlue);
    TCODConsole::root->setBackgroundColor(TCODColor::black);
    TCODMouse::showCursor (false);
    TCODConsole::root->clear();
    
    int px=7,py=7;

    m->computeFov(px,py);
    while (!endGame && !TCODConsole::isWindowClosed()) {
      for(int i=0;i<80;i++)
	for(int j=0;j<50;j++)
	  if(m->isInFov(i,j))
	    TCODConsole::root->setChar(i,j,'.');
      
      TCODConsole::root->setChar(px,py,'@');

      TCODConsole::flush();
      
      TCOD_key_t key=TCODConsole::waitForKeypress(true);
      if(key.vk==TCODK_LEFT)
	px--;
      if(key.vk==TCODK_RIGHT)
	px++;
      if(key.vk==TCODK_UP)
	py--;
      if(key.vk==TCODK_DOWN)
	py++;
      m->computeFov(px,py);
    }
    
    return 0;
}
