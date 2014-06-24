/*
** queue.h for queue in /home/sinet_l/Documents/project/zappy/libsocket
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat May  3 13:44:23 2014 luc sinet
** Last update Fri Jun 20 18:14:32 2014 luc sinet
*/

#ifndef _QUEUE_H_
# define _QUEUE_H_

typedef struct	s_queue t_queue;

struct		s_queue
{
  char		*msg;
  t_queue	*next;
};

int	queue_push(t_queue **queue, char *msg);
void	queue_pop(t_queue **queue);
void	shift_msg(char *msg, int pos);
void	queue_clear(t_queue **queue);
char	*queue_back(t_queue *queue);
char	*queue_front(t_queue *queue);
int	queue_empty(t_queue *queue);
int	queue_size(t_queue *queue);
t_queue	*queue_init();

#endif /* _QUEUE_H_ */
