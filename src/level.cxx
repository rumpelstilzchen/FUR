#include <list>
#include <cassert>
#include "level.hpp"

using namespace fur;

struct Level::private_state
{
  typedef std::list<SP<SquareObject> > rep_t;
  rep_t rep; //level representation is a linked list from the stl
};

Level::Level():ps(new Level::private_state)
{}

Level::~Level()
{
  delete ps;
}

void Level::addObject(SP<SquareObject> o)
{
  private_state::rep_t::iterator it = std::find(ps->rep.begin(),ps->rep.end(),o);
  assert(it==ps->rep.end()); //assert there are no findings of this SqObj in rep

  ps->rep.push_back(o);
}

std::list<SP<SquareObject> > Level::getPos(Position p)
{
  std::list<SP<SquareObject> > result;
  for(std::list<SP<SquareObject> >::const_iterator it = ps->rep.begin();
      it != ps->rep.end();
      it++)
    if((*it)->getPosition() == p)
      result.push_back(*it);
  return result;
}

/*
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{
  ifstream in ( "somefile" );
  if ( in.is_open() ) {
    string line;
    while ( getline ( in, line ) ) {
  15.
    string::size_type i = line.find_first_not_of ( " \t\n\v" );
  16.
       
  17.
    if ( i != string::npos && line[i] == '#' )
  18.
    continue;
  19.
       
  20.
    // Process non-comment line
  21.
    }
  22.
    }
  23.
    }
*/
