/*
** connection.c for connection in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:12:56 2014 luc sinet
** Last update Wed Jul  9 23:51:52 2014 guillaume fillon
*/

#include "server.h"
#include "scheduler.h"

int			connect_new_user(t_server *server)
{
  int			fd;
  struct sockaddr_in	client;
  socklen_t		size;
  t_client		*cl;

  size = sizeof(struct sockaddr_in);
  if ((fd = accept(server->fd, (struct sockaddr *)&client, &size)) == -1)
    return (iperror("accept", -1));
  cl = client_new(fd);
  if (cl == NULL)
    return (-1);
  list_add_elem_at_back(&server->cl, cl);
  queue_push(&cl->queue, "BIENVENUE\n");
  return (fd);
}

void		spread_inventory(t_world *world, t_player *pl)
{
  unsigned int	i;
  int		j;

  if (pl == NULL)
    return ;
  for (i = 0; i < sizeof(pl->inventory) / sizeof(int); ++i)
    {
      for (j = 0; j < pl->inventory[i]; ++j)
	add_to_world(world, i + FOOD, pl->x, pl->y);
    }
}

int		kick_user(t_list *list, t_client *cl, t_world *world)
{
  spread_inventory(world, cl->player);
  erase_client(world, cl);
  list_del_node(list, cl);
  return (2);
}

void		remove_associated_jobs(t_list *jobs, t_client *client)
{
  t_node	*node;
  t_job		*job;

  node = *jobs;
  while (node != NULL)
    {
      job = (t_job *)node->value;
      if (job->client == client)
	{
	  node = node->next;
	  list_del_node(jobs, job);
	  free(job);
	}
      else
	node = node->next;
    }
}

int	disconnect_user(t_server *server, t_client *client)
{
  if (server != NULL)
    remove_associated_jobs(&server->jobs, client);
  client->ghost = true;
  if (client->player->teamptr != NULL && client->player->level >= 8)
    client->player->teamptr->nb_of_level_max -= 1;
  return (2);
}
