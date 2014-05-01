/*
** ringbuffer.c for ringbuffer in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Apr 25 22:02:19 2014 luc sinet
** Last update Thu May  1 16:35:43 2014 luc sinet
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "ringbuffer.h"

void	align_ringbuffer(t_ringb *rb, char *tab, size_t tabsize)
{
  int	size;

  memset(tab, 0, tabsize);
  size = (rb->start <= rb->end) ?
    (rb->end - rb->start) :
    (rb->size - rb->start);
  strncpy(tab, &rb->buf[rb->start], size);
  if (rb->start > rb->end)
    strncat(tab, rb->buf, rb->end);
}

ssize_t		get_char_pos(t_ringb *rb, char *tab, char c)
{
  size_t	pos;

  if ((pos = (size_t)strchr(tab, c)) == 0)
    return (-1);
  rb->start = (rb->start + pos + 1) % rb->size;
  return (pos - (size_t)tab);
}

void		fill_ringbuffer(t_ringb *rb, char *buf, ssize_t bufsize)
{
  size_t	copysize;
  size_t 	i;

  i = 0;
  copysize = (bufsize == -1) ? strlen(buf) : (size_t)bufsize;
  while (i < copysize)
    {
      rb->buf[rb->end] = buf[i];
      rb->end = (rb->end + 1) % rb->size;
      ++i;
    }
}

void	free_ringbuffer(t_ringb *rb)
{
  free(rb->buf);
  free(rb);
}

t_ringb		*init_ringbuffer(size_t size)
{
  t_ringb	*rb;

  if ((rb = malloc(sizeof(t_ringb))) == NULL ||
      (rb->buf = malloc(size)) == NULL)
    {
      perror("init_ringbuffer: malloc");
      return (NULL);
    }
  rb->size = size;
  rb->start = 0;
  rb->end = 0;
  return (rb);
}

int main()
{
  return 0;
}
