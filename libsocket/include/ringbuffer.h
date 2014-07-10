/*
** ringbuffer.h for ringbuffer in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Apr 25 22:07:08 2014 luc sinet
** Last update Tue Jul  8 10:35:29 2014 luc sinet
*/

#ifndef _RINGBUFFER_H_
# define _RINGBUFFER_H_

# include <unistd.h>
# include "strings.h"

typedef struct	s_ringb
{
  char		*buf;
  t_string	string;
  size_t	size;
  size_t	start;
  size_t	end;
}		t_ringb;

void	align_ringbuffer(t_ringb *rb, char *tab, size_t tabsize);
ssize_t	get_char_pos(char *tab, char c);
void	fill_ringbuffer(t_ringb *rb, char *buf, ssize_t bufsize);
t_ringb	*create_ringbuffer(size_t size);
void	free_ringbuffer(t_ringb *rb);
char	*get_buff(t_ringb *rb);
void	update_ringbuffer(t_ringb *rb, char *init, char *used);
void	transfer_to_ringbuffer(t_ringb *rb);
void	transfer_to_string(t_ringb *rb, int *state);

#endif /* _RINGBUFFER_H_ */
