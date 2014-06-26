/*
** monitoring.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 19 15:28:17 2014 guillaume fillon
** Last update Thu Jun 26 20:42:38 2014 guillaume fillon
*/

#include <err.h>

#include "server.h"

int		dispatch_fds(t_server *server, struct epoll_event *ev)
{
  t_client	*tmp;

  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (tmp->fd == ev->data.fd)
	break;
    }
  if (tmp && tmp->fd != ev->data.fd)
    return (-1);
  if (ev->events & EPOLLIN)
    {
      if (read_state(server, tmp) < 0)
	return (-1);
    }
  if (write_state(server, tmp) < 0)
    return (-1);
  return (0);
}

static void		update_fds_to_epoll(t_server *server)
{
  struct epoll_event	ev;
  t_client		*tmp;

  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (tmp->ghost == true && queue_empty(tmp->queue))
	{
	  if (epoll_event_del(tmp->fd, NULL) == -1)
	    iperror("epoll_ctl: client", -1);
	  kick_user(server, tmp);
	  continue ;
	}
      ev.events = EPOLLIN | EPOLLONESHOT;
      if (!queue_empty(tmp->queue))
	ev.events |= EPOLLOUT;
      ev.data.ptr = NULL;
      ev.data.fd = tmp->fd;
      if (epoll_event_mod(tmp->fd, &ev) == -1)
	iperror("epoll_ctl: client", -1);
    }
}

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
      update_fds_to_epoll(server);
      nfds = epoll_monitor(events, MAX_EPOLL_EVENTS, 1000 / server->world.delay);
      if (nfds == -1)
	return (iperror("epoll_wait", -1));
      for (n = 0; n < nfds; ++n)
	{
	  if ((events[n].events & EPOLLERR) ||
              (events[n].events & EPOLLHUP))
	    {
	      close(events[n].data.fd);
	      epoll_event_del(events[n].data.fd, NULL);
	      continue;
	    }
	  if (events[n].data.fd == server->fd)
	    {
	      if ((fd = connect_new_user(server)) > 0)
		{
		  ev.events = EPOLLIN | EPOLLONESHOT;
		  ev.data.ptr = NULL;
		  ev.data.fd = fd;
		  if (epoll_event_add(fd, &ev) == -1)
		    return (iperror("epoll_ctl: client", -1));
		}
	    }
	  else
	    dispatch_fds(server, &events[n]);
	}
    }
}
