/*
** map_box.c for map_box in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Jun 22 23:10:38 2014 luc sinet
** Last update Fri Jun 27 17:20:35 2014 luc sinet
*/

#include "server.h"

char		*get_element_name(t_world *world, int x, int y,
				  unsigned int slot)
{
  static char	*names[NB_ELEM] = {"linemate", "deraumere", "sibur",
				   "mendiane", "phiras", "thystame",
				   "joueur"};
  int		pos;
  int		elem;

  pos = MAP_POS(x, y, world->width);
  if (world->map[pos]->content == NULL ||
      slot >= strlen(world->map[pos]->content))
    return (NULL);
  elem = world->map[pos]->content[slot];
  if (elem < LINEMATE || elem > PLAYER)
    return (NULL);
  return (strdup(names[elem - 1]));
}

int	add_to_world(t_world *world, int type, int x, int y)
{
  int	pos;
  char	tab[2];

  tab[1] = '\0';
  pos = MAP_POS(x, y, world->width);
  if (type > PLAYER)
    return (-1);
  tab[0] = type;
  return (string_append(world->map[pos], tab, AV_MAP) == NULL ? -1 : 0);
}

int	remove_from_world(t_world *world, int type, int x, int y)
{
  int	pos;

  pos = MAP_POS(x, y, world->width);
  if (type >= NB_ELEM)
    return (-1);
  return (string_clear(world->map[pos], type));
}
