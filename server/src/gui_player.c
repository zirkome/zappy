/*
** gui_player.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jun 24 13:50:43 2014 guillaume fillon
** Last update Tue Jul  1 14:55:41 2014 guillaume fillon
*/

#include "server.h"

int		gui_ppo(t_server *server, t_client *client, char *arg)
{
  char		*msg;
  t_client	*tmp;
  int		id;

  id = stoi(arg);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (tmp->player->id == id)
	{
	  msg = cnprintf(BUFSIZ, "ppo %d %d %d %d\n",
			 tmp->player->id,
			 tmp->player->x, tmp->player->y,
			 tmp->player->dir);
	  queue_push(&client->queue, msg);
	  free(msg);
	  return (0);
	}
    }
  queue_push(&client->queue, "sbp\n");
  return (-1);
}

int		gui_plv(t_server *server, t_client *client, char *arg)
{
  char		*msg;
  t_client	*tmp;
  int		id;

  id = stoi(arg);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (tmp->player->id == id)
	{
	  msg = cnprintf(BUFSIZ, "plv %d %d\n",
			 tmp->player->id,
			 tmp->player->level);
	  queue_push(&client->queue, msg);
	  free(msg);
	  return (0);
	}
    }
  queue_push(&client->queue, "sbp\n");
  return (-1);
}

int		gui_pin(t_server *server, t_client *client, char *arg)
{
  t_player	*pl;
  char		*msg;
  t_client	*tmp;
  int		id;

  id = stoi(arg);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      pl = tmp->player;
      if (pl->id == id)
	{
	  msg = cnprintf(BUFSIZ, "pin %d %d %d %d %d %d %d %d %d %d\n",
			 pl->id, pl->x, pl->y,
			 pl->inventory[0], pl->inventory[1],
			 pl->inventory[2], pl->inventory[3],
			 pl->inventory[4], pl->inventory[5],
			 pl->inventory[6]);
	  queue_push(&client->queue, msg);
	  free(msg);
	  return (0);
	}
    }
  queue_push(&client->queue, "sbp\n");
  return (-1);
}
