/*
** queue.h for queue in /home/sinet_l/Documents/project/zappy/libsocket
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat May  3 13:44:23 2014 luc sinet
** Last update Sat May  3 14:16:51 2014 luc sinet
*/

#ifndef _QUEUE_H_
# define _QUEUE_H_

typedef struct	s_queue t_queue;

struct		s_queue
{
  char		*msg;
  t_queue	*next;
};

int	add_to_queue(t_queue **queue, char *msg);
void	pop_msg(t_queue **queue);
void	shift_msg(char *msg, int pos);
void	erase_queue(t_queue **queue);
t_queue	*init_queue();

#endif /* _QUEUE_H_ */
