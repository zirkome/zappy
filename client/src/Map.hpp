#ifndef _MAP_HPP_
#define _MAP_HPP_

# include <iostream>
# include <list>
# include "Exception.hpp"
# include "Entity.hpp"

class Map
{
public:
  Map();
  virtual ~Map();

  void createMap(int, int);
  char &operator[](int) const;
  int getSize() const;
  void addPlayer(t_player *player);
  void addEgg(t_egg *egg);
  void display() const;

private:
  char *_map;
  std::list<t_player *> _player;
  std::list<t_egg *> _egg;
  int  _x;
  int  _y;
};

#endif /* _MAP_HPP_ */
