/*
** scheduler.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jul  1 15:52:59 2014 guillaume fillon
** Last update Wed Jul  2 22:36:23 2014 guillaume fillon
*/

#include "scheduler.h"

int		scheduler_add(t_scheduler *sched, struct s_job *task)
{
  struct s_job	*node;
  struct s_job	*job;

  job = malloc(sizeof(struct s_job));
  if (job == NULL)
    return (-1);
  memset(job, 0, sizeof(struct s_job));
  node = (struct s_job*) list_get_elem_at_back(*sched);
  job = memcpy(job, task, sizeof(struct s_job));
  if (node != NULL)
    job->at = node->at + job->at;
  else
    job->at = clock_getsecond() + job->at;
  printf("[SCHEDULER][ADD] now: %lu \tsched on: %lu\n", clock_getsecond(), job->at);
  list_add_elem_at_back(sched, job);
  return (0);
}

static int	check_job(struct s_job *job, time_t date, t_server *server)
{
  if (job != NULL && date >= job->at)
    {
      printf("[SCHEDULER][EXEC] now: %lu \tsched on: %lu\n", clock_getsecond(), job->at);
      job->callback(server, job->client, job->arg);
      list_del_node(&job->client->player->jobs, job);
      free(job->arg);
      free(job);
      return (0);
    }
  return (-1);
}

void		scheduler_update(t_list *clients, t_server *server)
{
  time_t	now;
  t_node	*cl;
  t_client	*tmp;

  now = clock_getsecond();
  for (cl = *clients; cl != NULL; cl = cl->next)
    {
      tmp = (t_client*)cl->value;
      if (tmp->player != NULL)
	check_job(list_get_elem_at_front(tmp->player->jobs), now, server);
    }
}
