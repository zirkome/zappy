/*
** ringbuffer.c for ringbuffer in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Apr 25 22:02:19 2014 luc sinet
** Last update Tue Jul  8 10:35:57 2014 luc sinet
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "ringbuffer.h"

void	update_ringbuffer(t_ringb *rb, char *init, char *used)
{
  int	pos;

  pos = (size_t)used - (size_t)init;
  free(init);
  if (rb->string.content == NULL || rb->string.content[0] == '\0')
    rb->start = (rb->start + pos) % rb->size;
  else
    {
      string_shift(&rb->string, pos);
      if (string_size(&rb->string) < (int)rb->size)
	transfer_to_ringbuffer(rb);
    }
}

ssize_t		get_char_pos(char *tab, char c)
{
  size_t	pos;

  if ((pos = (size_t)strchr(tab, c)) == 0)
    return (-1);
  pos -= (size_t)tab;
  return (pos);
}

void		fill_ringbuffer(t_ringb *rb, char *buf, ssize_t bufsize)
{
  size_t	copysize;
  size_t 	i;
  char		tab[2];
  int		state;

  i = 0;
  state = !(rb->string.content == NULL || rb->string.content[0] == '\0');
  tab[1] = '\0';
  copysize = (bufsize == -1) ? strlen(buf) : (size_t)bufsize;
  while (i < copysize)
    {
      tab[0] = buf[i];
      if (state == 0)
	{
	  rb->buf[rb->end] = buf[i];
	  rb->end = (rb->end + 1) % rb->size;
	  if (rb->end == rb->start)
	    transfer_to_string(rb, &state);
	}
      else
	string_append(&rb->string, tab, ALLOC_SIZE);
      ++i;
    }
}

void	free_ringbuffer(t_ringb *rb)
{
  string_clear(&rb->string);
  free(rb->buf);
  free(rb);
}

t_ringb		*create_ringbuffer(size_t size)
{
  t_ringb	*rb;

  if ((rb = malloc(sizeof(t_ringb))) == NULL ||
      (rb->buf = malloc(size)) == NULL)
    {
      perror("init_ringbuffer: malloc");
      return (NULL);
    }
  string_init(&rb->string);
  rb->size = size;
  rb->start = 0;
  rb->end = 0;
  return (rb);
}
