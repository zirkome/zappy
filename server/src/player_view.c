/*
** player_view.c for view in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Jun 26 14:48:57 2014 luc sinet
** Last update Thu Jun 26 14:52:35 2014 luc sinet
*/

#include "server.h"

int	append_from_view(t_world *world, t_player *pl,
			 t_string *string, int *idx)
{
  int	i;
  int	x;
  int	y;
  char	*elem;

  x = ((pl->dir == EAST || pl->dir == SOUTH) ? -idx[0] : idx[0]);
  y = ((pl->dir == SOUTH || pl->dir == WEST) ? -idx[1] : idx[1]);
  printf("%d %d\n", x, y);
  for (i = 0; (elem = get_element_name(world, pl->x + x,
				       pl->y + y, i)) != NULL; ++i)
    {
      if ((i > 0 && string_append(string, " ", ALLOC_SIZE) == NULL) ||
	  string_append(string, elem, ALLOC_SIZE) == NULL)
	return (iperror("get_view: malloc", -1));
      free(elem);
    }
  return (0);
}

int	get_view(t_world *world, t_player *pl, t_string *string)
{
  int	start;
  int	idx[2];

  for (idx[1] = 0; idx[1] < 4 + pl->level - 1; ++idx[1])
    {
      start = -idx[1];
      for (idx[0] = start; idx[0] < start + idx[1] * 2 + 1; ++idx[0])
	{
	  if (append_from_view(world, pl, string, idx) == -1)
	    return (-1);
	  if (idx[0] + 1 < start + idx[1] * 2 + 1)
	    if (string_append(string, ",", ALLOC_SIZE) == NULL)
	      return (iperror("get_view: malloc", -1));
	}
    }
  return (0);
}

int		pl_see(t_server *server, t_client *client,
		       char *arg UNUSED)
{
  t_player	*pl;
  t_string	string;

  pl = client->player;
  string_init(&string);
  if (string_append(&string, "{", ALLOC_SIZE) == NULL)
    return (iperror("pl_see: malloc", -1));
  get_view(&server->world, pl, &string);
  if (string_append(&string, "}\n", ALLOC_SIZE) == NULL)
    return (iperror("pl_see: malloc", -1));
  queue_push(&client->queue, string.content);
  free(string.content);
  return (0);
}
