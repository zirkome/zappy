/*
** vectors_get.c for vector in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jul  1 13:15:59 2014 luc sinet
** Last update Wed Jul  2 21:30:55 2014 luc sinet
*/

#include "server.h"

unsigned int	vector_size(t_vector *vector)
{
  unsigned int	i;

  if (vector->tab == NULL)
    return (0);
  for (i = 0; vector->tab[i] != NULL; ++i);
  return (i);
}

void		*vector_get(t_vector *vector, unsigned int pos)
{
  return (vector->tab[pos]);
}

void	*vector_front(t_vector *vector)
{
  return (vector->tab == NULL ? NULL : vector->tab[0]);
}

void	*vector_back(t_vector *vector)
{
  int	pos;

  pos = vector_size(vector) - 1;
  return (pos < 0 ? NULL : vector->tab[pos]);
}
