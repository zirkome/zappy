/*
** monitoring.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 19 15:28:17 2014 guillaume fillon
** Last update Thu Jun 19 16:25:46 2014 guillaume fillon
*/

#include <err.h>

#include "server.h"

//TODO: Norme
int			start_monitoring(t_server *server)
{
  int			nfds;
  int			n;
  int			fd;
  struct epoll_event	ev;
  struct epoll_event	events[MAX_EPOLL_EVENTS];

  epoll_create_monitor();
  ev.events = EPOLLIN;
  ev.data.ptr = NULL;
  ev.data.fd = server->fd;
  if (epoll_event_add(server->fd, &ev) == -1)
    {
      warn("epoll_ctl: listen_sock");
      return (-1);
    }
  for (;;)
    {
      nfds = epoll_monitor(events, MAX_EPOLL_EVENTS, -1);
      if (nfds == -1)
	return (iperror("epoll_wait", -1));
      for (n = 0; n < nfds; ++n)
	{
	  if ((events[n].events & EPOLLERR) ||
              (events[n].events & EPOLLHUP))
	    {
	      close (events[n].data.fd);
	      epoll_event_del(events[n].data.fd, NULL);
	      continue;
	    }
	  if (events[n].data.fd == server->fd)
	    {
	      if ((fd = connect_new_user(server)) > 0)
		{
		  ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
		  ev.data.ptr = NULL;
		  ev.data.fd = fd;
		  if (epoll_event_add(fd, &ev) == -1)
		    return (iperror("epoll_ctl: client", -1));
		}
	    }
	  else
	    {
	      if (events[n].events & EPOLLIN)
	      	read_state(server);
	      if (events[n].events & EPOLLOUT)
	      	write_state(server);
	    }
	}
    }
}
