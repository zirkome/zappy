/*
** gui_events.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jul  3 14:26:40 2014 guillaume fillon
** Last update Wed Jul  9 23:49:36 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_events_handling(t_server *server,
				    t_client *client,
				    t_gui_arg *arg,
				    t_gui_callback f)
{
  t_node	*tmp;

  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (((t_client*)tmp->value)->type == GRAPHIC)
	f(server, (t_client*)tmp->value, client, arg);
    }
  return (0);
}
