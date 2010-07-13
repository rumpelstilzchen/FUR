#ifndef __CONTAINER_HPP
#define __CONTAINER_HPP

#include <string>


namespace fur {

class Container
{
private:
  int capacity;
  std::string name; //does it have a name?
  enum {BAG, CHEST, SUITCASE, SAFE, BRAIN} type;
public:
  bool empty();
  bool size();
  bool size_free();
  void add(int); //change this to item
};

}
#endif
