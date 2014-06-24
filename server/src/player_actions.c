/*
** player_actions.c for actions in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:50:31 2014 luc sinet
** Last update Tue Jun 24 11:27:07 2014 luc sinet
*/

#include "server.h"

int	get_view(t_world *world, t_player *pl, t_string *string)
{
  char	*elem;
  int	start;
  int	i;
  int	x;
  int	y;

  for (y = 0; y < 4 + pl->level - 1; ++y)
    {
      start = -y;
      for (x = start; x < start + y * 2 + 1; ++x)
	{
	  for (i = 0; (elem = get_element_name(world, pl->x + x,
					       pl->y + y, i)) != NULL; ++i)
	    {
	      if ((i > 0 && string_append(string, " ", ALLOC_SIZE) == NULL) ||
		  string_append(string, elem, ALLOC_SIZE) == NULL)
		return (iperror("get_view: malloc", -1));
	      free(elem);
	    }
	  if (x + 1 < start + y * 2 + 1)
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

int	pl_take(t_server *server UNUSED, t_client *client UNUSED,
		char *arg UNUSED)
{
  return (0);
}

int	pl_put(t_server *server UNUSED, t_client *client UNUSED,
	       char *arg UNUSED)
{
  return (0);
}

int	pl_expulse(t_server *server UNUSED, t_client *client UNUSED,
		   char *arg UNUSED)
{
  return (0);
}
