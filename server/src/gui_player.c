/*
** gui_player.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jun 24 13:50:43 2014 guillaume fillon
** Last update Wed Jul  9 23:02:31 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_ppo(t_server *server, t_client *client, char *arg)
{
  char		*msg;
  t_node	*tmp;
  int		id;

  id = stoi(arg);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (((t_client*)tmp->value)->player->id == id)
	{
	  msg = cnprintf(BUFSIZ, "ppo %d %d %d %d\n",
			 ((t_client*)tmp->value)->player->id,
			 ((t_client*)tmp->value)->player->x,
			 ((t_client*)tmp->value)->player->y,
			 ((t_client*)tmp->value)->player->dir);
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
  t_node	*tmp;
  int		id;

  id = stoi(arg);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (((t_client*)tmp->value)->player->id == id)
	{
	  msg = cnprintf(BUFSIZ, "plv %d %d\n",
			 ((t_client*)tmp->value)->player->id,
			 ((t_client*)tmp->value)->player->level);
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
  t_node	*tmp;
  int		id;

  id = stoi(arg);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      pl = ((t_client*)tmp->value)->player;
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

int	gui_player_connect(UNUSED t_server *server, t_client *graphic,
			   t_client *client, UNUSED t_gui_arg *arg)
{
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "pnw %d %d %d %d %d %s\n",
		     pl->id,
		     pl->x, pl->y,
		     pl->dir,
		     pl->level,
		     pl->teamptr->name);
  return (0);
}
