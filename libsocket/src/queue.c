/*
** send_answer.c for send_answer in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Apr 20 08:27:21 2014 luc sinet
** Last update Thu Jun 26 19:25:59 2014 guillaume fillon
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

#include "queue.h"

int		queue_push(t_queue **queue, char *msg)
{
  t_queue	*tmp;
  t_queue	*new;

  tmp = *queue;
  if ((new = malloc(sizeof(t_queue))) == NULL ||
      (new->msg = strdup(msg)) == NULL)
    {
      warn("add_to_queue: malloc");
      return (-1);
    }
  new->next = NULL;
  if (!*queue)
    {
      *queue = new;
      return (0);
    }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  return (0);
}

void		queue_pop(t_queue **queue)
{
  t_queue	*tmp;

  tmp = *queue;
  if (tmp == NULL)
    return ;
  free(tmp->msg);
  *queue = tmp->next;
  free(tmp);
}

void	shift_msg(char *msg, int pos)
{
  int	i;

  i = 0;
  while (msg[pos])
    msg[i++] = msg[pos++];
  msg[i] = '\0';
}

void		queue_clear(t_queue **queue)
{
  t_queue	*tmp;
  t_queue	*next;

  tmp = *queue;
  while (tmp)
    {
      next = tmp->next;
      free(tmp->msg);
      free(tmp);
      tmp = next;
    }
  *queue = NULL;
}

t_queue	*queue_init()
{
  return (NULL);
}
