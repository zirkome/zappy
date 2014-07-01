/*
** vectors.c for vectors in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jul  1 09:57:48 2014 luc sinet
** Last update Tue Jul  1 11:26:14 2014 luc sinet
*/

#include "server.h"

int	vector_init(t_vector *vector)
{
  vector->tab = NULL;
  vector->size = 0;
  return (0);
}

int	vector_append(t_vector *vector, void *ent, int align_size)
{
  int	pos;
  int	new_size;

  if (vector->tab == NULL)
    pos = 0;
  else
    for (pos = 0; vector->tab[pos] != NULL; ++pos);
  if (pos + 1 >= vector->size)
    {
      new_size = (ALIGN(pos + ((pos == 0) ? 2 : 1) + 1, align_size));
      if ((vector->tab = realloc(vector->tab, sizeof(void *) *
				 new_size)) == NULL)
	return (iperror("vector_append: ", -1));
      vector->size = new_size;
    }
  vector->tab[pos] = ent;
  printf("tab[%d] = %p => %d\n", pos, ent, *((int *)(vector->tab[pos])));
  vector->tab[pos + 1] = NULL;
  return (0);
}

int	vector_erase(t_vector *vector, void *ent)
{
  int	i;

  if (vector->tab == NULL)
    return (-1);
  for (i = 0; vector->tab[i] != NULL && vector->tab[i] != ent; ++i);
  if (vector->tab[i] == NULL)
    return (-1);
  for (; vector->tab[i] != NULL; ++i)
    vector->tab[i] = vector->tab[i + 1];
  return (0);
}

int	vector_erase_pos(t_vector *vector, int pos)
{
  int	i;

  if (vector->tab == NULL)
    return (-1);
  for (i = 0; vector->tab[i] != NULL; ++i);
  if (pos >= i)
    return (-1);
  for (; vector->tab[pos] != NULL; ++pos)
    vector->tab[pos] = vector->tab[pos + 1];
  return (0);
}

void	vector_clear(t_vector *vector)
{
  free(vector->tab);
  vector->tab = NULL;
  vector->size = 0;
}
