/*
** gui_team_win.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 16:00:28 2014 guillaume fillon
** Last update Tue Jul  8 16:26:54 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int	gui_team_win(UNUSED t_server *server, t_client *graphic,
		     UNUSED t_client *client, UNUSED t_gui_arg *arg)
{
  queue_push_message(&graphic->queue, "seg %s\n", arg->msg);
  return (0);
}
