/*
** init.c for init in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 09:39:44 2014 luc sinet
** Last update Fri May  2 09:54:16 2014 luc sinet
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
  serv->maxfd = 3;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &serv->r_fd);
      FD_SET(tmp->fd, &serv->w_fd);
      ++serv->maxfd;
      tmp = tmp->next;
    }
}

int		init_serv(t_serv *serv, int ac, char **av)
{
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR ||
      signal(SIGINT, &handle_signal) == SIG_ERR)
    return (iperror("init_serv: signal", -1));
  if ((serv->fd = create_inet_server_socket(NULL, (ac == 1) ?
					    "6000" : av[1])) < 0)
    return (-1);
  return (0);
}
