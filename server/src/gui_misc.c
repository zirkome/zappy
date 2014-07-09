/*
** gui_misc.c for project in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 26 21:14:01 2014 guillaume fillon
** Last update Mon Jul  7 10:35:02 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_welcome(t_server *server, t_client *client)
{
  char		*msg;
  t_node	*tmp;
  t_player	*pl;
  int		ret;

  ret = gui_msz(server, client, NULL);
  ret |= gui_sgt(server, client, NULL);
  ret |= gui_mct(server, client, NULL);
  ret |= gui_tna(server, client, NULL);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (((t_client*)tmp->value)->type == IA)
	{
	  pl = ((t_client*)tmp->value)->player;
	  msg = cnprintf(BUFSIZ, "pnw %d %d %d %d %d %s\n",
			 pl->id, pl->x, pl->y,
			 pl->dir, pl->level, pl->teamptr->name);
	  queue_push(&client->queue, msg);
	  free(msg);
	}
    }
  return (ret);
}
