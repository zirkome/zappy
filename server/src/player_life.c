/*
** player_life.c for life in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jul  4 00:30:30 2014 luc sinet
** Last update Fri Jul  4 11:33:23 2014 luc sinet
*/

#include "scheduler.h"
#include "server.h"

void		update_living_state(t_server *server, t_client *client,
				    time_t now)
{
  t_job		*task;

  task = client->player->foodjob;
  if (task == NULL)
    {
      if ((client->player->foodjob = malloc(sizeof(t_job))) == NULL)
	return ;
      task = client->player->foodjob;
      task->client = client;
      task->at = now + FOODTIME / server->world.delay;
      task->callback = NULL;
      task->arg = NULL;
      return ;
    }
  if (now >= task->at)
    {
      task->at = now + FOODTIME / server->world.delay;
      if ((--(client->player->inventory[FOOD - 1])) < 0)
	{
	  queue_push(&client->queue, "mort\n");
	  disconnect_user(NULL, client);
	}
    }
}

int	handle_player_life(t_server *server, t_client *client,
			   time_t now)
{
  if (client->type == IA)
    update_living_state(server, client, now);
  return (0);
}
