/*
** ring_buffer.h for rb in libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Mon Apr 14 14:28:24 2014 guillaume fillon
** Last update Sun Apr 27 17:50:18 2014 guillaume fillon
*/

#ifndef _RING_BUFFER_H_
# define _RING_BUFFER_H_

# include <stddef.h>
# include <sys/types.h>

typedef struct
{
  char		*buf;
  size_t	length;
  int		start;
  int		end;
}		t_ring_buffer;

void	rb_init(t_ring_buffer *rb, size_t length);
void	rb_destroy(t_ring_buffer *rb);

ssize_t	rb_read(t_ring_buffer *rb, char *target, size_t amount);
ssize_t	rb_write(t_ring_buffer *rb, char *data, size_t length);
char	*rb_get(t_ring_buffer *rb, size_t amount);
ssize_t	rb_write_format(t_ring_buffer *rb, char *format, ...)
  __attribute__((format(printf, 2, 3)));

size_t	rb_available_data(t_ring_buffer *rb);
size_t	rb_available_space(t_ring_buffer *rb);
char	*rb_starts_at(t_ring_buffer *rb);
char	*rb_ends_at(t_ring_buffer *rb);
void	rb_commit_write(t_ring_buffer *rb, size_t amount);
void	rb_commit_read(t_ring_buffer *rb, size_t amount);

#endif /* _RING_BUFFER_H_ */
