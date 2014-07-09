/*
** gui_time.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jun 24 13:52:40 2014 guillaume fillon
** Last update Mon Jun 30 16:47:31 2014 guillaume fillon
*/

#include "server.h"

int	gui_sgt(t_server *server, t_client *client, UNUSED char *arg)
{
  char	*msg;

  msg = cnprintf(BUFSIZ, "sgt %lu\n", server->world.delay);
  queue_push(&client->queue, msg);
  free(msg);
  return (0);
}

int		gui_sst(t_server *server, t_client *client, char *arg)
{
  time_t	delay;

  delay = stoi(arg);
  if (delay <= 0)
    server->world.delay = 1;
  else
    server->world.delay = delay;
  gui_sgt(server, client, NULL);
  return (0);
}
