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

char &Map::operator[](int coord) const
{
  if (_map != NULL && coord >= 0 && coord <= _x * _y)
    return (_map[coord]);
  throw(Exception("Not in the map"));
}

int Map::getSize() const
{
  return (_x * _y);
}

void Map::addPlayer(t_player *player)
{
  if (player->nb < 0 || (player->x < 0 || player->x > _x)
      || (player->y < 0 || player->y > _y) || (player->lvl < 0 || player->lvl > 8)
      || (player->orient < NORTH || player->orient > WEST))
    delete player;
  else
    _player.push_back(player);
}

void Map::addEgg(t_egg *egg)
{
  if (egg->nb < 0 || (egg->x < 0 || egg->x > _x) || (egg->y < 0 || egg->y > _y))
    delete egg;
  else
    _egg.push_back(egg);
}

void Map::display() const
{
  if (!_map)
    return ;
  for (int x = 0;x < _x;++x)
    {
      for (int y = 0;y < _y;++y)
	{
	  std::cout << _map[x * _y + y];
	}
      std::cout << std::endl;
    }
}
