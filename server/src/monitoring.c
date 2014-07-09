/*
** monitoring.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 19 15:28:17 2014 guillaume fillon
** Last update Wed Jul  9 14:16:57 2014 guillaume fillon
*/

#include <err.h>

#include "scheduler.h"
#include "server.h"

int		dispatch_fds(t_server *server, struct epoll_event *ev)
{
  t_node	*tmp;

  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (((t_client *)tmp->value)->fd == ev->data.fd)
	break;
    }
  if (tmp == NULL || ((t_client *)tmp->value)->fd != ev->data.fd)
    return (-1);
  if (ev->events & EPOLLIN)
    {
      if (read_state(server, (t_client *)tmp->value) < 0)
	return (-1);
    }
  if (write_state(server, (t_client *)tmp->value) < 0)
    return (-1);
  return (0);
}

static void		update_fds_to_epoll(t_server *server)
{
  struct epoll_event	ev;
  t_node		*tmp;
  t_client		*client;

  for (tmp = server->cl; tmp != NULL;)
    {
      client = ((t_client*)tmp->value);
      if (client->ghost == true && queue_empty(client->queue))
	{
	  if (client->type != EGG && epoll_event_del(client->fd, NULL) == -1)
	    iperror("epoll_ctl: client", -1);
	  tmp = tmp->next;
	  kick_user(&server->cl, client, &server->world);
	  free(client);
	  continue ;
	}
      else if (client->type == EGG)
	{
	  tmp = tmp->next;
	  continue ;
	}
      create_event(&ev, client->fd, EPOLLIN | EPOLLONESHOT);
      if (!queue_empty(client->queue))
	ev.events |= EPOLLOUT;
      if (epoll_event_mod(client->fd, &ev) == -1)
      	iperror("epoll_ctl: client", -1);
      tmp = tmp->next;
    }
}

static int		dispatch_events(t_server *server,
					int nfds,
					struct epoll_event
					events[MAX_EPOLL_EVENTS])
{
  int			fd;
  int			n;
  struct epoll_event	ev;

  for (n = 0; n < nfds; ++n)
    {
      if ((events[n].events & EPOLLERR) || (events[n].events & EPOLLHUP))
	{
	  close(events[n].data.fd);
	  epoll_event_del(events[n].data.fd, NULL);
	  continue;
	}
      if (events[n].data.fd == server->fd)
	{
	  if ((fd = connect_new_user(server)) > 0)
	    {
	      create_event(&ev, fd, EPOLLIN | EPOLLONESHOT);
	      if (epoll_event_add(fd, &ev) == -1)
		return (iperror("epoll_ctl: client", -1));
	    }
	}
      else
	dispatch_fds(server, &events[n]);
    }
  return (0);
}

int			start_monitoring(t_server *server)
{
  int			nfds;
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
      nfds = epoll_monitor(events, MAX_EPOLL_EVENTS, 100);
      scheduler_update(&server->cl, server);
      if (nfds == -1)
	return (iperror("epoll_wait", -1));
      dispatch_events(server, nfds, events);
    }
}
