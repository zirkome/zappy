/*
** scheduler.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jul  1 15:52:59 2014 guillaume fillon
** Last update Sat Jul  5 13:48:40 2014 luc sinet
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

void		update_food(t_world *world, t_node *clients)
{
  unsigned int	food;
  unsigned int	i;
  unsigned int	size;

  for (food = 0; clients != NULL; clients = clients->next)
    if (((t_client *)clients->value)->player != NULL)
      food += ((t_client *)clients->value)->player->inventory[FOOD - 1];
  for (i = 0, size = world->width * world->height; i < size; ++i)
    food += count_type_on_box(world, FOOD, i % world->width, i / world->width);
  if (FOODLIMIT(size, food))
    for (size = size - 1; food > 0 && size > 0; --size)
      if (food >= rand() % size)
	{
	  add_to_world(world, FOOD, size % world->width, size / world->width);
	  --food;
	}
}

void		scheduler_update(t_list *clients, t_server *server)
{
  time_t	now;
  t_node	*cl;
  t_client	*tmp;

  now = clock_getsecond();
  if (now >= server->world.food_check)
    {
      update_food(&server->world, *clients);
      server->world.food_check = now + 5;
    }
  for (cl = *clients; cl != NULL; cl = cl->next)
    {
      tmp = (t_client*)cl->value;
      if (tmp->player != NULL)
	{
	  if (tmp->type == IA || tmp->type == EGG)
	    update_living_state(server, tmp, now, tmp->type);
	  check_job(list_get_elem_at_front(tmp->player->jobs), now, server);
	}
   }
}
