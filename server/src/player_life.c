/*
** player_life.c for life in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jul  4 00:30:30 2014 luc sinet
** Last update Wed Jul  9 12:09:27 2014 luc sinet
*/

#include "scheduler.h"
#include "server.h"
#include "gui.h"

void	init_client_foodjob(t_server *server, t_client *client, time_t now)
{
  t_job	*task;

  if ((client->player->foodjob = malloc(sizeof(t_job))) == NULL)
    return ;
  task = client->player->foodjob;
  task->client = client;
  task->at = now + FOODTIME / server->world.delay;
  task->callback = NULL;
  task->arg = NULL;
}

void		rotten_egg(t_server *server, t_client *client)
{
  t_gui_arg	garg;

  garg.id = client->player->id;
  if (client->player->teamptr->slots > 0)
    --client->player->teamptr->slots;
  disconnect_user(NULL, client);
  gui_events_handling(server, client, &garg, &gui_egg_dead);
}

void	update_living_state(t_server *server, t_client *client,
			    time_t now, t_client_type type)
{
  t_job	*task;

  task = client->player->foodjob;
  if (task == NULL)
    {
      init_client_foodjob(server, client, now);
      return ;
    }
  if (now >= task->at)
    {
      task->at = now + FOODTIME / server->world.delay;
      if ((--(client->player->inventory[FOOD - 1])) < 0)
	{
	  if (type == IA)
	    {
	      gui_events_handling(server, client, NULL, &gui_player_dead);
	      queue_push(&client->queue, "mort\n");
	      disconnect_user(NULL, client);
	    }
	  else
	    rotten_egg(server, client);
	}
    }
}
