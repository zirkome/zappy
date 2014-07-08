/*
** gui_expulse.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 14:47:11 2014 guillaume fillon
** Last update Mon Jul  7 16:57:41 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_expulse(t_server *server, t_client *graphic,
			    t_client *client, UNUSED t_gui_arg *arg)
{
  t_node	*tmp;
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "pex %d\n", pl->id);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      pl = ((t_client*)tmp->value)->player;
      if (((t_client*)tmp->value)->type == IA)
	queue_push_message(&graphic->queue, "ppo %d %d %d %d\n",
			   pl->id, pl->x, pl->y, pl->dir);
    }
  return (0);
}
