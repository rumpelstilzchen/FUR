#include <iostream>
#include "libtcod.hpp"
#include "squareobject.hpp"

using namespace std;

int main()
{
    TCODConsole::initRoot(80,50,"my game",false);
    TCODMap*m = new TCODMap (100, 100);
    m->setProperties (1,1, false, true);

    int x = 5, y = 8;
    TCODLine::init(x,y,13,4);
    do {
    // update cell x,y
    } while (!TCODLine::step(&x,&y));

    int endGame=0;

    while ( ! endGame && ! TCODConsole::isWindowClosed() ) {
//    ... draw on TCODConsole::root
        TCODConsole::root->setBackgroundColor(TCODColor::desaturatedRed);
        TCODMouse::showCursor (false);
        TCODConsole::root->setChar(3, 4, 53);
        TCODConsole::flush();

        TCOD_key_t key=TCODConsole::waitForKeypress(true);
//    ... update world, using key
    }

    return 0;
}
