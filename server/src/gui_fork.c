/*
** gui_fork_start.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 16:00:37 2014 guillaume fillon
** Last update Tue Jul  8 13:09:18 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int	gui_fork_start(t_server *, t_client *, t_client *, t_gui_arg *);

int	gui_fork_end(UNUSED t_server *server, t_client *graphic,
		     t_client *client, t_gui_arg *arg)
{
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "enw %d %d %d %d\n",
		     arg->id, pl->id, pl->x, pl->y);
  return (0);
}
