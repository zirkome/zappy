/*
** gui_movements.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Mon Jul  7 11:31:47 2014 guillaume fillon
** Last update Mon Jul  7 11:37:42 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_movements(UNUSED t_server *server, t_client *graphic,
			      t_client *client, UNUSED t_gui_arg *arg)
{
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "ppo %d %d %d %d\n",
		     pl->id, pl->x, pl->y, pl->dir);
  return (0);
}
