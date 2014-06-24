/*
** init.c for init in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 09:39:44 2014 luc sinet
** Last update Tue Jun 24 16:41:22 2014 guillaume fillon
*/

#include <signal.h>

#include "server.h"

int		init_server(t_server *server)
{
  if (server->world.port == NULL)
    server->world.port = DEFAULT_PORT;
  if ((server->fd = create_inet_server_socket(NULL, server->world.port)) < 0)
    return (-1);
  if (server->world.delay == 0)
    server->world.delay = 1;
  server->cl = NULL;
  srand(time(NULL));
  if (generate_map(&server->world) == -1)
    return (-1);
  welcome_server(server->world.port);
  return (0);
}
