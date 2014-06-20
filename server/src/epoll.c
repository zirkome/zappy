/*
** epoll.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Mon Jun 16 11:53:48 2014 guillaume fillon
** Last update Thu Jun 19 15:53:30 2014 guillaume fillon
*/

#include <sys/epoll.h>
#include <err.h>

#include "server.h"

static int	g_epfd = 0;

int	epoll_event_add(int fd, struct epoll_event *ev)
{
  if (g_epfd <= 0)
    return (-1);
  return (epoll_ctl(g_epfd, EPOLL_CTL_ADD, fd, ev));
}

int	epoll_event_mod(int fd, struct epoll_event *ev)
{
  if (g_epfd <= 0)
    return (-1);
  return (epoll_ctl(g_epfd, EPOLL_CTL_MOD, fd, ev));
}

int	epoll_event_del(int fd, struct epoll_event *ev)
{
  if (g_epfd <= 0)
    return (-1);
  return (epoll_ctl(g_epfd, EPOLL_CTL_DEL, fd, ev));
}

int	epoll_monitor(struct epoll_event events[], int maxevents, int timeout)
{
  if (g_epfd <= 0)
    return (-1);
  return (epoll_wait(g_epfd, events, maxevents, timeout));
}

int	epoll_create_monitor()
{
  if (g_epfd > 0)
    return (g_epfd);
  g_epfd = epoll_create1(0);
  if (g_epfd < 0)
    {
      warn("epoll_create1");
      return (-1);
    }
  return (g_epfd);
}
