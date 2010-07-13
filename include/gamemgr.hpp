#ifndef __GAME_MGR_HPP
#define __GAME_MGR_HPP

#include <string>
#include "util.hpp"
#include "player.hpp"
#include "level.hpp"
#include <list>
#include "message.hpp"
#include "libtcod.hpp"
#include "libtcod_int.h"
#include "messagewindow.hpp"

namespace fur
{
  class GameMgr
  {
  private:
    //singleton foo
    GameMgr();
    ~GameMgr();
    GameMgr(const GameMgr &);             // intentionally undefined
    GameMgr & operator=(const GameMgr &); // intentionally undefined

    //private state
    struct private_state;
    private_state* ps;

    std::list<Message > currentStrings; //currentStrings
    MessageWindow * messagewindow;

    int cnt; //delete this

  public:
    enum GAME_STATUS {RUNNING,QUIT,WON,LOST};

    SP<Player> getPlayer() const;
    SP<Level> getLevel() const;

    void setGameStatus(GAME_STATUS);

    void enterGameLoop();

    void msg(std::string msg,TCOD_bkgnd_flag_t flag,const TCODColor colour);                      //prints to standard Area.
    void msg(std::string msg); //writes with current background colour
    void msg(Message m);

    //singleton foo
    static GameMgr &getInstance();
  };
}

#endif //__GAME_MGR_HPP
