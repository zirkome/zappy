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
  unsigned char &operator[](int) const;
  void addPlayer(t_player *player);
  void updatePlayerPos(int nb, int x, int y, int orient);
  void updatePlayerLvl(int nb, int lvl);
  void updatePlayerAction(int nb, Action act);
  void addEgg(t_egg *egg);
  void display() const;

  int getSize() const;
  int getX() const;
  int getY() const;

private:
  unsigned char *_map;
  std::list<t_player *> _player;
  std::list<t_egg *> _egg;
  int  _x;
  int  _y;
};

#endif /* _MAP_HPP_ */
