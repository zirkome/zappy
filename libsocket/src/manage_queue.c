/*
** manage_queue.c for manage_queue in /home/sinet_l/Documents/project/zappy/libsocket
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat May  3 14:58:51 2014 luc sinet
** Last update Mon Jun 30 11:23:48 2014 luc sinet
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

int		queue_append_back(t_queue **queue, char *msg)
{
  t_queue	*back;
  int		old_len;

  if (!queue)
    return (queue_push(queue, msg));
  for (back = *queue; back->next != NULL; back = back->next);
  old_len = (back->msg == NULL ? 0 : strlen(back->msg));
  if ((back->msg = realloc(back->msg, old_len + strlen(msg) + 1)) == NULL)
    return (-1);
  if (old_len == 0)
    back->msg[0] = '\0';
  strcat(back->msg, msg);
  return (0);
}
