#ifndef _MAP_HPP_
#define _MAP_HPP_

# include <iostream>
# include <list>

typedef struct	s_coord
{
  int		x;
  int		y;
}		t_coord;

class Map
{
public:
  Map();
  virtual ~Map();

  void createMap(int, int);
  char operator[](int) const;
  int getSize() const;

private:
  char *_map;
  std::list<t_coord> _player;
  int  _x;
  int  _y;
};

#endif /* _MAP_HPP_ */
