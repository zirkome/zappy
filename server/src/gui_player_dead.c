/*
** gui_player_dead.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 16:00:59 2014 guillaume fillon
** Last update Tue Jul  8 13:17:27 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int	gui_player_dead(UNUSED t_server *server, t_client *graphic,
			t_client *client, UNUSED t_gui_arg *arg)
{
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "pdi %d\n", pl->id);
  return (0);
}
