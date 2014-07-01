/*
** handle_user.c for handle in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 12:29:40 2014 luc sinet
** Last update Tue Jul  1 18:42:57 2014 luc sinet
*/

#include "server.h"

static int	g_increment = 1;

static int	init_player(t_client *new)
{
  if ((new->player = malloc(sizeof(t_player))) == NULL)
    return (iperror("init_player: malloc", -1));
  new->player->dir = NORTH;
  new->player->x = 0;
  new->player->y = 0;
  new->player->level = 1;
  new->player->id = g_increment++;
  new->player->teamptr = NULL;
  memset(new->player->inventory, 0, sizeof(new->player->inventory));
  return (0);
}

static void	init_client(t_client *client, int fd)
{
  client->fd = fd;
  client->ghost = false;
  client->type = UNKNOWN;
  client->queue = queue_init();
}

t_client	*client_new(int fd)
{
  t_client	*new;

  if ((new = malloc(sizeof(t_client))) == NULL)
    return (ptperror("client_new: malloc", NULL));
  else if ((new->rb = create_ringbuffer(1024)) == NULL ||
	   init_player(new) == -1)
    {
      free(new);
      return (NULL);
    }
  init_client(new, fd);
  return (new);
}
