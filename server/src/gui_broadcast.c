/*
** gui_broadcast.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 16:00:44 2014 guillaume fillon
** Last update Mon Jul  7 15:01:52 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_broadcast(UNUSED t_server *server, t_client *graphic,
			      t_client *client, t_gui_arg *arg)
{
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "pbc %d %s\n",
		     pl->id, arg->msg);
  return (0);
}
