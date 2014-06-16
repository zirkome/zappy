/*
** init.c for init in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 09:39:44 2014 luc sinet
** Last update Mon Jun 16 10:18:11 2014 guillaume fillon
*/

#include <signal.h>
#include "server.h"

void		init_fds(t_server *server)
{
  t_client	*tmp;

  tmp = server->cl;
  FD_ZERO(&server->r_fd);
  FD_ZERO(&server->w_fd);
  FD_SET(server->fd, &server->r_fd);
  FD_SET(server->fd, &server->w_fd);
  server->maxfd = server->fd;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &server->r_fd);
      if (!queue_empty(tmp->queue))
	FD_SET(tmp->fd, &server->w_fd);
      if (tmp->fd > server->maxfd)
	server->maxfd = tmp->fd;
      tmp = tmp->next;
    }
  ++server->maxfd;
}

int		init_server(t_server *server)
{
  if (server->world.port == NULL)
    server->world.port = DEFAULT_PORT;
  if ((server->fd = create_inet_server_socket(NULL, server->world.port)) < 0)
    return (-1);
  server->cl = NULL;
  welcome_server(server->world.port);
  return (0);
}
