#ifndef __GAME_MGR_HPP
#define __GAME_MGR_HPP

#include <string>
#include "util.hpp"
#include "player.hpp"
#include "level.hpp"
#include <list>

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

    std::list<std::string > currentStrings; //currentStrings
    int cnt; //delete this

  public:
    enum GAME_STATUS {RUNNING,QUIT,WON,LOST};

    SP<Player> getPlayer() const;
    SP<Level> getLevel() const;

    void setGameStatus(GAME_STATUS);

    void enterGameLoop();

    void msg(std::string msg);                          //prints to standard rectangle
    void msg(std::string msg,int x,int y,int w,int h);  //prints to rectangle
    void msgLine(std::string msg);                      //prints to standard Area.



    //singleton foo
    static GameMgr &getInstance();
  };
}

#endif //__GAME_MGR_HPP
