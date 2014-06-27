/*
** gui_time.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jun 24 13:52:40 2014 guillaume fillon
** Last update Fri Jun 27 23:03:18 2014 guillaume fillon
*/

#include "server.h"

int	gui_sgt(t_server *server, t_client *client, UNUSED char *arg)
{
  char	*msg;

  msg = cnprintf(15, "sgt %d\n", server->world.delay);
  queue_push(&client->queue, msg);
  free(msg);
  return (0);
}

int	gui_sst(UNUSED t_server *server, UNUSED t_client *client, UNUSED char *arg)
{
  return (0);
}
