#ifndef __GAME_MGR_HPP
#define __GAME_MGR_HPP

#include "util.hpp"
#include "player.hpp"
#include "level.hpp"

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

  public:
    enum GAME_STATUS {RUNNING,QUIT,WON,LOST};

    SP<Player> getPlayer() const;
    SP<Level> getLevel() const;

    void setGameStatus(GAME_STATUS);

    void enterGameLoop();
  
    //singleton foo
    static GameMgr &getInstance();
  };
}

#endif //__GAME_MGR_HPP
