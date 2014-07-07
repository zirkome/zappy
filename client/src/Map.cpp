#include "Map.hpp"

Map::Map(): _map(NULL), _x(0), _y(0)
{

}

Map::~Map()
{
  if (_map != NULL)
    delete _map;
  while (!_egg.empty())
    {
      delete _egg.front();
      _egg.pop_front();
    }
  while (!_player.empty())
    {
      delete _player.front();
      _player.pop_front();
    }
}

void Map::createMap(int x, int y)
{
  if (_map != NULL)
    delete _map;
  _map = new unsigned char[x * y];
  std::memset(_map, 0, x * y * sizeof(char));
  while (!_egg.empty())
    {
      delete _egg.front();
      _egg.pop_front();
    }
  while (!_player.empty())
    {
      delete _player.front();
      _player.pop_front();
    }
  _x = x;
  _y = y;
}

unsigned char &Map::operator[](int coord) const
{
  if (_map != NULL && coord >= 0 && coord <= _x * _y)
    return (_map[coord]);
  throw(Exception("Not in the map"));
}

int Map::getSize() const
{
  return (_x * _y);
}

int Map::getX() const
{
  return (_x);
}

int Map::getY() const
{
  return (_y);
}

std::list<t_egg *>::const_iterator Map::getEggBegin() const
{
  return (_egg.begin());
}

std::list<t_egg *>::const_iterator Map::getEggEnd() const
{
  return (_egg.end());
}

std::list<t_player *>::const_iterator Map::getPlayerBegin() const
{
  return (_player.begin());
}

std::list<t_player *>::const_iterator Map::getPlayerEnd() const
{
  return (_player.end());
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

void Map::updatePlayerPos(int nb, int x, int y, int orient)
{
  if ((x < 0 || x > _x) || (y < 0 || y > _y)
      || (orient < NORTH || orient > WEST))
    return ;
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->x = x;
	(*it)->y = y;
	(*it)->orient = orient;
	return ;
      }
}


void Map::updatePlayerLvl(int nb, int lvl)
{
  if (lvl < 0 || lvl > 8)
    return ;
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->lvl = lvl;
	return ;
      }
}

void Map::updatePlayerAction(int nb, Action act)
{
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->cuAction = act;
	return ;
      }
}

void Map::updatePlayerInventory(int nb, int inventory[])
{
  for (std::list<t_player *>::iterator it = _player.begin();it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	for (int i = 0;i < 7;++i)
	  (*it)->inventory[i] = inventory[i];
	return ;
      }
}

void Map::deletePlayer(int nb)
{
  for (std::list<t_player *>::iterator it = _player.begin(); it != _player.end();++it)
    if ((*it)->nb == nb)
      {
	_player.erase(it);
	return ;
      }
}

void Map::addEgg(t_egg *egg)
{
  if (egg->nb < 0 || (egg->x < 0 || egg->x > _x) || (egg->y < 0 || egg->y > _y))
    delete egg;
  else
    _egg.push_back(egg);
}

void Map::updateStateEgg(int nb, State state)
{
  for (std::list<t_egg *>::iterator it = _egg.begin(); it != _egg.end();++it)
    if ((*it)->nb == nb)
      {
	(*it)->cuState = state;
	return ;
      }
}

void Map::deleteEgg(int nb)
{
  for (std::list<t_egg *>::iterator it = _egg.begin(); it != _egg.end();++it)
    if ((*it)->nb == nb)
      {
	_egg.erase(it);
	return ;
      }
}

void Map::display() const
{
  if (!_map)
    return ;
  for (int x = 0;x < _x;++x)
    {
      for (int y = 0;y < _y;++y)
	{
	  std::cout << static_cast<int>(_map[x * _y + y]) << "\t";
	}
      std::cout << std::endl;
    }
}
