#include "position.hpp"
#include "squareobject.hpp"

#ifndef __ANIMAL_HPP
#define __ANIMAL_HPP



class Animal : public SquareObject //?
{
private:
  char symbol;
public:
  Animal(char symbol);
  Position getPos();
  void setPosition(Position);
  char getSymbol();
};

#endif //__ANIMAL_HPP
