/*
** player_actions.c for actions in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:50:31 2014 luc sinet
** Last update Fri Jun 27 22:35:05 2014 luc sinet
*/

#include "server.h"

int		pl_take(t_server *server, t_client *client,
			char *arg)
{
  t_player	*pl;
  int		elem_id;
  int		pos;

  pl = client->player;
  pos = MAP_POS(pl->x, pl->y, server->world.width);
  if ((elem_id = get_element_id(arg)) == -1 ||
      string_erase(server->world.map[pos], elem_id) == -1)
    {
      queue_push(&client->queue, "ko\n");
      return (-1);
    }
  add_to_inventory(pl, elem_id, 1);
  queue_push(&client->queue, "ok\n");
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
