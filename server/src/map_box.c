/*
** map_box.c for map_box in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Jun 22 23:10:38 2014 luc sinet
** Last update Sun Jun 22 23:48:02 2014 luc sinet
*/

#include "server.h"

char		*get_element_name(t_world *world, int x, int y)
{
  int		pos;
  static char	*names[NB_ELEM] = {"linemate", "deraumere", "sibur",
				   "mendiane", "phiras", "thystame", "joueur"};

  printf("Asking for %d %d\n", x, y);
  pos = MAP_POS(x, y, world->width);
  if (world->map[pos] >= NB_ELEM)
    return (NULL);
  return (strdup(names[(int)world->map[pos]]));
}
