/*
** player_movement.c for moves in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:47:25 2014 luc sinet
** Last update Thu Jul  3 22:32:46 2014 luc sinet
*/

#include "server.h"

int		pl_forward(t_server *server, t_client *client,
			   char *arg UNUSED)
{
  t_player	*pl;

  pl = client->player;
  remove_from_world(&server->world, PLAYER, pl->x, pl->y);
  pl->x += ((pl->dir == WEST) ? -1 : (pl->dir == EAST) ? 1 : 0);
  pl->y += ((pl->dir == SOUTH) ? 1 : (pl->dir == NORTH) ? -1 : 0);
  apply_map_looping(&pl->x, &pl->y, server->world.width, server->world.height);
  add_to_world(&server->world, PLAYER, pl->x, pl->y);
  queue_push(&client->queue, "ok\n");
  return (0);
}

int	pl_right(t_server *server UNUSED, t_client *client,
		 char *arg UNUSED)
{
  if ((++client->player->dir) > WEST)
    client->player->dir = NORTH;
  queue_push(&client->queue, "ok\n");
  return (0);
}

int	pl_left(t_server *server UNUSED, t_client *client,
		char *arg UNUSED)
{
  if (client->player->dir == NORTH)
    client->player->dir = WEST;
  else
    --client->player->dir;
  queue_push(&client->queue, "ok\n");
  return (0);
}
