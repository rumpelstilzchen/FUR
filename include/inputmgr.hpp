#ifndef __INPUT_MGR_HPP
#define __INPUT_MGR_HPP

/*
 * The InputMgr handles key input. This involves trying to move the
 * player if arrow keys are being pressed.
 * Like all *Mgr classes, it is a singleton class.
 */

namespace fur
{
  class InputMgr
  {
  private:
    // singleton foo
    InputMgr() {}
    ~InputMgr() {}
    InputMgr(const InputMgr&); //intentionally undefined
    InputMgr& operator=(const InputMgr&); //intentionally undefined
  public:
    void waitForInput();
  
    // singleton foo
    static InputMgr& getInstance();
  };
}

#endif // __INPUT_MGR_HPP
