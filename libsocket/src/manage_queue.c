/*
** manage_queue.c for manage_queue in /home/sinet_l/Documents/project/zappy/libsocket
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat May  3 14:58:51 2014 luc sinet
** Last update Sat May  3 15:35:08 2014 luc sinet
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "queue.h"

char		*queue_back(t_queue *queue)
{
  if (!queue)
    return (NULL);
  while (queue->next)
    queue = queue->next;
  return (queue->msg);
}

char	*queue_front(t_queue *queue)
{
  return (queue == NULL ? NULL : queue->msg);
}

int	queue_empty(t_queue *queue)
{
  return (queue == NULL);
}

int	queue_size(t_queue *queue)
{
  int	size;

  size = 0;
  while (queue)
    {
      queue = queue->next;
      ++size;
    }
  return (size);
}
