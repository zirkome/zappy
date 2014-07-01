/*
** player_commands.c for player_commands in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 14:03:33 2014 luc sinet
** Last update Tue Jul  1 17:57:15 2014 luc sinet
*/

#include "server.h"
#include "egg.h"

int	pl_incantation(t_server *server UNUSED, t_client *client UNUSED,
		       char *arg UNUSED)
{
  return (0);
}

int	pl_fork(t_server *server, t_client *client,
		char *arg UNUSED)
{
  t_egg	*new;

  if ((new = lay_egg(client->player)) == NULL)
    return (-1);
  return (vector_append(server->world.egg, new, ALLOC_SIZE));
}

int	pl_connect_nbr(t_server *server UNUSED, t_client *client,
		       char *arg UNUSED)
{
  char	tab[32];

  snprintf(tab, 32, "%d\n", client->player->teamptr->slots);
  return (queue_push(&client->queue, tab));
}
