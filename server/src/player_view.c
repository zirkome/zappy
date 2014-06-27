/*
** player_view.c for view in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Jun 26 14:48:57 2014 luc sinet
** Last update Fri Jun 27 21:41:41 2014 luc sinet
*/

#include "server.h"

void	apply_map_looping(int *x, int *y, int wdx, int wdy)
{
  if (*x >= wdx)
    *x %= wdx;
  else if (*x < 0)
    {
      *x = ABS(*x);
      if (*x > wdx)
	*x %= wdx;
      *x = wdx - *x;
    }
  if (*y >= wdy)
    *y %= wdy;
  else if (*y < 0)
    {
      *y = ABS(*y);
      if (*y > wdy)
	*y %= wdy;
      *y = wdy - *y;
    }
}

void	apply_point_rotation(t_dir dir, int *x, int *y)
{
  int	save;

  if (dir == NORTH)
    return ;
  if (dir == EAST)
    {
      save = *x;
      *x = *y;
      *y = -save;
    }
  else if (dir == SOUTH)
    {
      *x = -(*x);
      *y = -(*y);
    }
  else
    {
      save = *x;
      *x = -(*y);
      *y = save;
    }
}

int	append_from_view(t_world *world, t_player *pl,
			 t_string *string, int *idx)
{
  int	i;
  int	x;
  int	y;
  char	*elem;

  x = idx[0];
  y = idx[1];
  apply_point_rotation(pl->dir, &x, &y);
  x += pl->x;
  y += pl->y;
  apply_map_looping(&x, &y, world->width, world->height);
  for (i = 0; (elem = get_element_name(world, x, y, i)) != NULL; ++i)
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

  for (idx[1] = 0; idx[1] < pl->level + 1; ++idx[1])
    {
      start = -idx[1];
      for (idx[0] = start; idx[0] < start + idx[1] * 2 + 1; ++idx[0])
	{
	  if (append_from_view(world, pl, string, idx) == -1)
	    return (-1);
	  if (idx[0] + 1 < start + pl->level * 2 + 1)
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
