/*
** ringbuffer_transfer.c for transfer in /home/sinet_l/Documents/project/zappy/libsocket/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jul  8 10:34:02 2014 luc sinet
** Last update Tue Jul  8 10:36:15 2014 luc sinet
*/

#include "ringbuffer.h"

void	transfer_to_string(t_ringb *rb, int *state)
{
  char	*buf;

  if ((buf = malloc(rb->size + 1)) == NULL)
    return ;
  align_ringbuffer(rb, buf, rb->size + 1);
  string_append(&rb->string, buf, ALLOC_SIZE);
  free(buf);
  *state = 1;
}

void	transfer_to_ringbuffer(t_ringb *rb)
{
  int	i;
  char	*buf;

  i = 0;
  buf = rb->string.content;
  while (buf[i])
    {
      rb->buf[rb->end] = buf[i];
      rb->end = (rb->end + 1) % rb->size;
      ++i;
    }
}

void	align_ringbuffer(t_ringb *rb, char *tab, size_t tabsize)
{
  int	size;

  memset(tab, 0, tabsize);
  size = ((rb->start < rb->end) ?
	  (rb->end - rb->start) :
	  (rb->size - rb->start));
  strncpy(tab, &rb->buf[rb->start], size);
  if (rb->start > rb->end)
    {
      size += rb->end;
      strncat(tab, rb->buf, rb->end);
    }
}

char	*get_buff(t_ringb *rb)
{
  char	*str;

  if (rb->string.content == NULL || rb->string.content[0] == '\0')
    {
      if ((str = malloc(rb->size + 1)) == NULL)
	return (NULL);
      align_ringbuffer(rb, str, rb->size + 1);
    }
  else
    str = strdup(rb->string.content);
  return (str);
}
