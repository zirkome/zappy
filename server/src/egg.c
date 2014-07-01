/*
** egg.c for egg in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jul  1 15:50:15 2014 luc sinet
** Last update Tue Jul  1 18:47:26 2014 luc sinet
*/

#include "server.h"
#include "egg.h"

t_egg	*lay_egg(t_player *pl)
{
  t_egg	*egg;

  if ((egg = malloc(sizeof(t_egg))) == NULL)
    return (NULL);
  egg->x = pl->x;
  egg->y = pl->y;
  egg->remaining_time = 0;
  return (egg);
}

int		egg_hatching(t_server *server, t_egg *egg)
{
  t_client	*client;


  if ((client = client_new(-1)) == NULL)
    return (-1);
  list_add_elem_at_back(&server->cl, client);
  add_to_world(&server->world, PLAYER, client->player->x, client->player->y);
  client->type = EGG;
  return (vector_erase(server->world.egg, egg));
}
