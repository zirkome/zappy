/*
** incantation_calcul.c for incant_calcul in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Wed Jul  2 21:28:52 2014 luc sinet
** Last update Thu Jul  3 11:23:18 2014 luc sinet
*/

#include "server.h"

void		get_player_at_pos(t_vector *vec, t_list list, int x, int y)
{
  t_client	*client;

  while (list != NULL)
    {
      client = list->value;
      if (client->type == IA && client->player->x == x && client->player->y == y)
	if (vector_append(vec, client, ALLOC_SIZE) == -1)
	  return ;
      list = list->next;
    }
}

int	needed_same_level(int lev)
{
  if (lev == 1)
    return (1);
  if (lev % 2 == 1)
    ++lev;
  return (lev + 2);
}

int		num_same_level(t_vector *vec, int lev)
{
  unsigned int	size;
  t_client	*client;
  int		counter;
  unsigned int 	i;

  size = vector_size(vec);
  counter = 0;
  for (i = 0; i < size; ++i)
    {
      client = vector_get(vec, i);
      if (client->player->level == lev)
	++counter;
    }
  return (counter);
}
