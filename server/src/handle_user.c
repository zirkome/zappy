/*
** handle_user.c for handle in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 12:29:40 2014 luc sinet
** Last update Thu Jun 26 21:49:29 2014 guillaume fillon
*/

#include "server.h"

static int	init_player(t_client *new)
{
  if ((new->player = malloc(sizeof(t_player))) == NULL)
    return (iperror("init_player: malloc", -1));
  new->player->dir = NORTH;
  new->player->x = 0;
  new->player->y = 0;
  new->player->level = 1;
  return (0);
}

static void	init_client(t_client *client, int fd)
{
  client->fd = fd;
  client->ghost = false;
  client->type = UNKNOWN;
  client->queue = queue_init();
  client->teamptr = NULL;
  client->next = NULL;
}

int		add_user(t_client **cl, int fd)
{
  t_client	*new;
  t_client	*tmp;

  tmp = *cl;
  if ((new = malloc(sizeof(t_client))) == NULL)
    return (iperror("add_user: malloc", -1));
  else if ((new->rb = create_ringbuffer(1024)) == NULL ||
	   init_player(new) == -1)
    return (-1);
  init_client(new, fd);
  if (*cl == NULL)
    {
      *cl = new;
      return (0);
    }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  return (0);
}
