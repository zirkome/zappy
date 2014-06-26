#include "Map.hpp"

Map::Map(): _map(NULL), _x(0), _y(0)
{

}

Map::~Map()
{
  if (_map != NULL)
    delete _map;
}

void Map::createMap(int x, int y)
{
  _map = new char[x * y];
  _x = x;
  _y = y;
}

char Map::operator[](int coord) const
{
  if (coord >= 0 && coord <= _x * _y)
    return (_map[coord]);
  return (-1);
}

int Map::getSize() const
{
  return (_x * _y);
}
