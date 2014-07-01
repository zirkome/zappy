/*
** monitoring.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 19 15:28:17 2014 guillaume fillon
** Last update Tue Jul  1 20:26:29 2014 guillaume fillon
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
  if (tmp && ((t_client *)tmp->value)->fd != ev->data.fd)
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
  t_node		*tmp2;
  t_client		*tofree;

  for (tmp = server->cl, tofree = NULL; tmp != NULL;)
    {
      if (tofree != NULL)
      	{
      	  free(tofree);
      	  tofree = NULL;
      	}
      if (((t_client*)tmp->value)->ghost == true &&
	  queue_empty(((t_client*)tmp->value)->queue))
	{
	  if (epoll_event_del(((t_client*)tmp->value)->fd, NULL) == -1)
	    iperror("epoll_ctl: client", -1);
	  tofree = (t_client*)tmp->value;
	  tmp2 = tmp->next;
	  kick_user(&server->cl, (t_client*)tmp->value, &server->world);
	  tmp = tmp2;
	  continue ;
	}
      ev.events = EPOLLIN | EPOLLONESHOT;
      if (!queue_empty(((t_client*)tmp->value)->queue))
	ev.events |= EPOLLOUT;
      ev.data.ptr = NULL;
      ev.data.fd = ((t_client*)tmp->value)->fd;
      if (epoll_event_mod(((t_client*)tmp->value)->fd, &ev) == -1)
	iperror("epoll_ctl: client", -1);
      tmp = tmp->next;
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
      nfds = epoll_monitor(events, MAX_EPOLL_EVENTS, 100);
      scheduler_update(&server->sched, server);
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
