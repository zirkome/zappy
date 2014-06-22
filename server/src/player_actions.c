/*
** player_actions.c for actions in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:50:31 2014 luc sinet
** Last update Sun Jun 22 23:47:55 2014 luc sinet
*/

#include "server.h"

int		pl_see(t_server *server, t_client *client,
		       char *arg UNUSED)
{
  t_player	*pl;
  int		start;
  int		str_size;
  char		*elem;
  char		*str;

  pl = client->player;
  str = NULL;
  str_size = 0;
  if ((str = string_append(str, "{", &str_size)) == NULL)
    return (iperror("pl_see: malloc", -1));
  for (int y = 0; y < 4 + pl->level - 1; ++y)
    {
      start = -y;
      for (int x = start; x < start + y * 2 + 1; ++x)
	{
	  if ((elem = get_element_name(&server->world, x, y)) != NULL)
	    if ((str = string_append(str, elem, &str_size)) == NULL)
	      return (iperror("pl_see: malloc", -1));
	  if (x + 1 < start + y * 2 + 1)
	    if ((str = string_append(str, ",", &str_size)) == NULL)
	      return (iperror("pl_see: malloc", -1));
	  free(elem);
	}
    }
  if ((str = string_append(str, "}\n", &str_size)) == NULL)
    return (iperror("pl_see: malloc", -1));
  queue_push(&client->queue, str);
  free(str);
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

int	pl_broadcast(t_server *server UNUSED, t_client *client UNUSED,
		     char *arg UNUSED)
{
  return (0);
}
