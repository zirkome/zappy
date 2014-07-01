/*
** scheduler.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jul  1 15:52:59 2014 guillaume fillon
** Last update Tue Jul  1 20:29:13 2014 guillaume fillon
*/

#include "scheduler.h"

int		scheduler_add(t_scheduler *sched, struct s_job *task)
{
  struct s_job	*job;

  job = malloc(sizeof(struct s_job));
  if (job == NULL)
    return (-1);
  memset(job, 0, sizeof(struct s_job));
  job = memcpy(job, task, sizeof(struct s_job));
  list_add_elem_at_back(sched, job);
  return (0);
}

static int	check_job(struct s_job *job, time_t date, t_server *server)
{
  if (date >= job->at)
    {
      printf("now: %lu \tsched on: %lu\n", clock_getsecond(), job->at);
      job->callback(server, job->client, job->arg);
      list_del_node(&server->sched, job);
      free(job);
      return (0);
    }
  return (-1);
}

void		scheduler_update(t_scheduler *sched, t_server *server)
{
  time_t	now;
  t_node	*tmp;
  t_node	*job;

  now = clock_getsecond();
  for (job = *sched; job != NULL;)
    {
      tmp = job->next;
      if (check_job((struct s_job*)job->value, now, server) == 0)
	{
	  job = tmp;
	  continue ;
	}
      job = job->next;
    }
}
