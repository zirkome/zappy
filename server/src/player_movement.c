/*
** player_movement.c for moves in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:47:25 2014 luc sinet
** Last update Thu Jun 26 17:16:04 2014 luc sinet
*/

#include "server.h"

int		pl_forward(t_server *server UNUSED, t_client *client,
			   char *arg UNUSED)
{
  t_player	*pl;

  pl = client->player;
  pl->x += ((pl->dir == WEST) ? -1 : (pl->dir == EAST) ? 1 : 0);
  pl->y += ((pl->dir == SOUTH) ? -1 : (pl->dir == NORTH) ? 1 : 0);
  queue_push(&client->queue, "ok\n");
  return (0);
}

int	pl_right(t_server *server, t_client *client, char *arg)
{
  if ((++client->player->dir) > WEST)
    client->player->dir = NORTH;
  pl_forward(server, client, arg);
  return (0);
}

int	pl_left(t_server *server, t_client *client, char *arg)
{
  if (client->player->dir == NORTH)
    client->player->dir = WEST;
  else
    --client->player->dir;
  pl_forward(server, client, arg);
  return (0);
}
