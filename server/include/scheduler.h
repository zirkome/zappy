/*
** scheduler.h for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jul  1 15:25:16 2014 guillaume fillon
** Last update Tue Jul  1 20:14:46 2014 guillaume fillon
*/

#ifndef _SCHEDULER_H_
# define _SCHEDULER_H_

# include "server.h"

struct		s_job
{
  t_client	*client;
  time_t	at;
  t_callback	callback;
  char		*arg;
};

typedef t_list t_scheduler;

/*
** Useful time functions
*/
time_t	clock_getsecond();
long	clock_getnanosecond();

/*
** Scheduler functions
*/
int	scheduler_add(t_scheduler *sched, struct s_job *task);
void	scheduler_update(t_scheduler *sched, t_server *server);

#endif /* _SCHEDULER_H_ */
