/*
** player_life.c for life in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jul  4 00:30:30 2014 luc sinet
** Last update Fri Jul  4 00:36:23 2014 luc sinet
*/

#include "scheduler.h"
#include "server.h"

void		update_living_state(t_server *server, t_client *cl)
{
  t_job		*task;
  time_t	now;

  task = cl->player->foodjob;
  now = clock_getsecond();
  if (task == NULL)
    {
      if ((task = malloc(sizeof(t_job))) == NULL)
	return ;
      task->client = cl;
      task->at = now + FOODTIME / server->world.delay;
      task->callback = NULL;//g_command[idx].func;
      task->arg = NULL;
      return ;
    }
  if (now >= task->at)
    {
      task->at = now + FOODTIME / server->world.delay;
      if ((--(cl->player->inventory[FOOD])) < 0)
	{
	  queue_push(&cl->queue, "mort\n");
	  disconnect_user(NULL, cl);
	}
    }
}

int	handle_player_life(t_server *server, t_client *client)
{
  if (client->type == IA)
    update_living_state(server, client);
  return (0);
}
