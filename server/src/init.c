/*
** init.c for init in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 09:39:44 2014 luc sinet
** Last update Sun May  4 17:14:37 2014 guillaume fillon
*/

#include <signal.h>
#include "server.h"

void		init_fds(t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->cl;
  FD_ZERO(&serv->r_fd);
  FD_ZERO(&serv->w_fd);
  FD_SET(serv->fd, &serv->r_fd);
  FD_SET(serv->fd, &serv->w_fd);
  serv->maxfd = serv->fd;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &serv->r_fd);
      if (!queue_empty(tmp->queue))
	FD_SET(tmp->fd, &serv->w_fd);
      if (tmp->fd > serv->maxfd)
	serv->maxfd = tmp->fd;
      tmp = tmp->next;
    }
  ++serv->maxfd;
}

int		init_serv(t_serv *serv)
{
  if (serv->world.port == NULL)
    serv->world.port = DEFAULT_PORT;
  if ((serv->fd = create_inet_server_socket(NULL, serv->world.port)) < 0)
    return (-1);
  serv->cl = NULL;
  welcome_server(serv->world.port);
  return (0);
}
