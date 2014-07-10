/*
** player_commands.c for player_commands in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 14:03:33 2014 luc sinet
** Last update Wed Jul  9 18:54:54 2014 guillaume fillon
*/

#include "scheduler.h"
#include "server.h"
#include "gui.h"

int		pl_fork_start(t_server *server, t_client *client,
			      char *arg UNUSED)
{
  struct s_job	task;

  task.client = client;
  task.at = 42.0f / server->world.delay;
  task.callback = &pl_lay_egg;
  task.arg = NULL;
  gui_events_handling(server, client, NULL, &gui_fork_start);
  return (scheduler_add(&client->player->jobs, &task));
}

int		pl_lay_egg(t_server *server, t_client *client,
			   char *arg UNUSED)
{
  t_gui_arg	garg;
  t_client	*new;
  struct s_job	task;

  if ((new = client_new(-1)) == NULL)
    return (-1);
  new->player->x = client->player->x;
  new->player->y = client->player->y;
  new->player->teamptr = client->player->teamptr;
  new->type = EGG_HATCHING;
  list_add_elem_at_back(&server->cl, new);
  task.client = new;
  task.at = 600.0f / server->world.delay;
  task.callback = &pl_fork;
  task.arg = NULL;
  queue_push(&client->queue, "ok\n");
  garg.id = new->player->id;
  gui_events_handling(server, client, &garg, &gui_fork_end);
  return (scheduler_add(&new->player->jobs, &task));
}

int		pl_fork(t_server *server, t_client *client,
			char *arg UNUSED)
{
  t_gui_arg	garg;

  client->type = EGG;
  add_to_world(&server->world, PLAYER, client->player->x, client->player->y);
  client->player->teamptr->slots += 1;
  garg.id = client->player->id;
  gui_events_handling(server, client, &garg, &gui_egg_born);
  return (queue_push(&client->queue, "ok\n"));
}

int	pl_connect_nbr(t_server *server UNUSED, t_client *client,
		       char *arg UNUSED)
{
  char	tab[32];

  snprintf(tab, 32, "%d\n", client->player->teamptr->slots);
  return (queue_push(&client->queue, tab));
}
