/*
** player_actions.c for actions in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:50:31 2014 luc sinet
** Last update Sun Jun 22 20:26:02 2014 luc sinet
*/

#include "server.h"

int		pl_see(t_server *server UNUSED, t_client UNUSED *client UNUSED,
		       char *arg UNUSED)
{
  t_player	*pl;
  int		start;
  int		str_size;
  char		*str;

  pl = client->player;
  str = NULL;
  str_size = 0;
  for (int y = 0; y < 4 + pl->level - 1; ++y)
    {
      start = -y;
      for (int x = start; x < start + y * 2 + 1; ++x)
	str = string_append(str, "a", &str_size);
    }
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
