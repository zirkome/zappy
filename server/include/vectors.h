/*
** vectors.h for vectors in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jul  1 10:11:49 2014 luc sinet
** Last update Tue Jul  1 13:47:29 2014 luc sinet
*/

#ifndef _VECTORS_H_
# define _VECTORS_H_

typedef struct	s_vector
{
  void		**tab;
  int		size;
}		t_vector;

void		vector_init(t_vector *vector);
int		vector_append(t_vector *vector, void *ent, int align_size);
int		vector_erase(t_vector *vector, void *ent);
int		vector_erase_pos(t_vector *vector, int pos);
void		vector_clear(t_vector *vector);
unsigned int	vector_size(t_vector *vector);
void		*vector_get(t_vector *vector, unsigned int pos);
void		*vector_front(t_vector *vector);
void		*vector_back(t_vector *vector);

#endif /* _VECTORS_H_ */
