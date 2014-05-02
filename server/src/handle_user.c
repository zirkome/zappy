/*
** handle_user.c for handle in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 12:29:40 2014 luc sinet
** Last update Fri May  2 22:21:01 2014 luc sinet
*/

#include "server.h"

int		add_user(t_client **cl, int fd)
{
  t_client	*new;
  t_client	*tmp;

  tmp = *cl;
  if ((new = malloc(sizeof(t_client))) == NULL)
    return (iperror("create_chan: malloc", -1));
  else if ((new->rb = create_ringbuffer(512)) == NULL)
    return (-1);
  new->fd = fd;
  new->next = NULL;
  if (*cl == NULL)
    {
      *cl = new;
      return (0);
    }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  return (0);
}
