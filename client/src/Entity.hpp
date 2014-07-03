#ifndef _ENTITY_HPP_
# define _ENTITY_HPP_

enum
  {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,

    FOOD = 1,
    LINEMATE = 2,
    DERAUMERE = 4,
    SIBUR = 8,
    MENDIANE = 16,
    PHIRAS = 32,
    THYSTAME = 64,
  };

enum Action
  {
    NOTHING = 0,
    LAY = 1,
    LEVELUP = 2,
    DROP = 3,
    LOOT = 4,
  };

enum State
  {
    NOT_HATCHING = 0,
    HATCHING = 1,
  };

typedef struct	s_egg
{
  s_egg(int posX, int posY, int number)
    : isAlive(true), cuState(NOT_HATCHING), x(posX), y(posY), nb(number) {};

  bool		isAlive;
  State		cuState;
  int		x;
  int		y;
  int		nb;
}		t_egg;

typedef struct	s_player
{
  s_player(int number, int posX, int posY, int cuLevel, int o, std::string t)
    : isAlive(true), nb(number), x(posX), y(posY), lvl(cuLevel), orient(o),
      cuAction(NOTHING), team(t) {};

  bool		isAlive;
  int		nb;
  int		x;
  int		y;
  int		lvl;
  int		orient;
  int		inventory[7];
  Action	cuAction;
  std::string   team;
}		t_player;


#endif /* _ENTITY_HPP_ */
