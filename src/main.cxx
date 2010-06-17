#include <iostream>
#include "libtcod.hpp"
#include "squareobject.hpp"

using namespace std;

int main()
{
  int winSizeX = 80, winSizeY = 50;
  TCODConsole::initRoot(winSizeX,winSizeY,"FUR",false);
  int mapSizeX = 100, mapSizeY = 100;
  TCODMap*m = new TCODMap (mapSizeX,mapSizeY);
  //    m->setProperties (5,5,true,false);
  for (int i=0;i<50;i++)
    for (int j=0;j<50;j++)
      m->setProperties(i,j,true,true);

  int endGame=0;


  //    const char *font="terminal.png";
  TCODConsole::root->setForegroundColor(TCODColor::lightBlue);
  TCODConsole::root->setBackgroundColor(TCODColor::black);
  TCODMouse::showCursor (false);
  TCODConsole::root->clear();

  int px=7,py=7; //startpos

  m->computeFov(px,py);
  while (!endGame && !TCODConsole::isWindowClosed()) {
    for (int i=0;i<80;i++)
      for (int j=0;j<50;j++)
        if (m->isInFov(i,j))  TCODConsole::root->setChar(i,j,'.');
    //zufällig zeichnen
    TCODConsole::root->setChar(10,15,'1');
    TCODConsole::root->setChar(10,20,'2');
    TCODConsole::root->setChar(10,30,'3');
    TCODConsole::root->setChar(15,40,'4');

    TCODConsole::root->setChar(px,py,'@');

//test
    //TCODConsole::root->hline(1,0, 50, TCOD_BKGND_SET);
    //TCODConsole::root->vline(0,1, 49, TCODConsole::root->);
    TCODConsole::root->printFrame(0,0,50,50,false,TCOD_BKGND_SET,NULL);
    TCODConsole::root->flush();

    TCOD_key_t key=TCODConsole::waitForKeypress(true);
    if (key.vk==TCODK_LEFT)
      px--;
    if (key.vk==TCODK_RIGHT)
      px++;
    if (key.vk==TCODK_UP)
      py--;
    if (key.vk==TCODK_DOWN)
      py++;
    if (key.vk==TCODK_ESCAPE)
      endGame=1;

    m->computeFov(px,py); //compute new fov

  }

  return 0;
}
