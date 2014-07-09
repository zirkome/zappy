/*
** gui_egg_born.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 16:00:50 2014 guillaume fillon
** Last update Wed Jul  9 11:49:00 2014 luc sinet
*/

#include "server.h"
#include "gui.h"

int	gui_egg_born(UNUSED t_server *server, t_client *graphic,
		     UNUSED t_client *client, t_gui_arg *arg)
{
  queue_push_message(&graphic->queue, "eht %d\n", arg->id);
  return (0);
}

int	gui_egg_dead(UNUSED t_server *server, t_client *graphic,
		     UNUSED t_client *client, t_gui_arg *arg)
{
  queue_push_message(&graphic->queue, "edi %d\n", arg->id);
  return (0);
}

int	gui_egg_connect(UNUSED t_server *server, t_client *graphic,
			UNUSED t_client *client, t_gui_arg *arg)
{
  queue_push_message(&graphic->queue, "ebo %d\n", arg->id);
  return (0);
}
