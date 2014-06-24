/*
** map_box.c for map_box in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Jun 22 23:10:38 2014 luc sinet
** Last update Tue Jun 24 09:52:22 2014 luc sinet
*/

#include "server.h"

char		*get_element_name(t_world *world, int x, int y,
				  unsigned int slot)
{
  int		pos;
  static char	*names[NB_ELEM] = {"linemate", "deraumere", "sibur",
				   "mendiane", "phiras", "thystame", "joueur"};
  int		elem;

  pos = MAP_POS(x, y, world->width);
  if (world->map[pos]->content == NULL ||
      slot >= strlen(world->map[pos]->content))
    return (NULL);
  elem = world->map[pos]->content[slot];
  if (elem >= NB_ELEM || elem < 0)
    return (NULL);
  return (strdup(names[elem]));
}
