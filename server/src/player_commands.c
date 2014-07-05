/*
** player_commands.c for player_commands in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 14:03:33 2014 luc sinet
** Last update Sat Jul  5 15:54:14 2014 luc sinet
*/

#include "scheduler.h"
#include "server.h"

int		pl_lay_egg(t_server *server, t_client *client,
			   char *arg UNUSED)
{
  struct s_job	task;

  task.client = client;
  task.at = 600.0f / server->world.delay;
  task.callback = &pl_fork;
  task.arg = NULL;
  return (scheduler_add(&client->player->jobs, &task));
}

int		pl_fork(t_server *server, t_client *client,
			char *arg UNUSED)
{
  t_client	*new;

  if ((new = client_new(-1)) == NULL)
    return (-1);
  new->player->x = client->player->x;
  new->player->y = client->player->y;
  new->player->teamptr = client->player->teamptr;
  new->type = EGG;
  list_add_elem_at_back(&server->cl, new);
  add_to_world(&server->world, PLAYER, new->player->x, new->player->y);
  new->player->teamptr->slots += 1;
  return (queue_push(&client->queue, "ok\n"));
}

int	pl_connect_nbr(t_server *server UNUSED, t_client *client,
		       char *arg UNUSED)
{
  char	tab[32];

  snprintf(tab, 32, "%d\n", client->player->teamptr->slots);
  return (queue_push(&client->queue, tab));
}
