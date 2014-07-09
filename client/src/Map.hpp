#ifndef _MAP_HPP_
#define _MAP_HPP_

# include <iostream>
# include <cstring>
# include <list>
# include <glm/glm.hpp>
# include "Exception.hpp"
# include "Entity.hpp"
# include "Line.hpp"

typedef struct	s_broadcast
{
  s_broadcast(float x1, float y1, float x2, float y2)
    : line(x1, y1, x2, y2), timeout(120) {}
  Line		line;
  int		timeout;
}		t_broadcast;

class Map
{
public:
  Map();
  virtual ~Map();

  void createMap(const int, const int);
  unsigned int *operator[](const int) const;
  void addPlayer(t_player *player);
  void updatePlayerPos(const int nb, const int x, const int y, const int orient);
  void updatePlayerLvl(const int nb, const int lvl);
  void updatePlayerAction(const int nb, Action act);
  void updatePlayerInventory(const int nb, const int inventory[]);
  void deletePlayer(const int nb);
  void addEgg(t_egg *egg);
  void updateStateEgg(const int nb, State state);
  void deleteEgg(const int nb);
  void addBroadcast(const int nb);
  void updateBroadcast();

  int getSize() const;
  int getX() const;
  int getY() const;

  std::list<t_egg *>::const_iterator getEggBegin() const;
  std::list<t_egg *>::const_iterator getEggEnd() const;

  std::list<t_player *>::const_iterator getPlayerBegin() const;
  std::list<t_player *>::const_iterator getPlayerEnd() const;

  std::list<t_broadcast *>::const_iterator getBroadcastBegin() const;
  std::list<t_broadcast *>::const_iterator getBroadcastEnd() const;

private:
  unsigned int **_map;
  std::list<t_player *> _player;
  std::list<t_egg *> _egg;
  std::list<t_broadcast *>  _broadcast;
  int  _x;
  int  _y;
};

#endif /* _MAP_HPP_ */
