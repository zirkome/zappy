/*
** map_player.c for map_player in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 28 10:52:08 2014 luc sinet
** Last update Sat Jun 28 11:20:58 2014 luc sinet
*/

#include "server.h"

int	count_type_on_box(t_world *world, int type, int x, int y)
{
  int	count;
  int	pos;
  int	i;

  count = 0;
  pos = MAP_POS(x, y, world->width);
  if (world->map[pos]->content == NULL)
    return (0);
  for (i = 0; world->map[pos]->content[i]; ++i)
    if (world->map[pos]->content[i] == type)
      ++count;
  return (count);
}

t_client       	*get_client_by_pos(t_client *cl, t_world *world,
				   int x, int y)
{
  t_client	*tmp;

  if (cl == NULL ||
      (count_type_on_box(world, PLAYER, x, y) <= 0))
    return (NULL);
  for (tmp = cl; tmp != NULL; ++tmp)
    {
      if (tmp->player->x == x && tmp->player->y == y)
	return (tmp);
    }
  return (NULL);
}
