/*
** map.c for map in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Jun 22 20:33:00 2014 luc sinet
** Last update Sun Jun 22 21:31:13 2014 luc sinet
*/

#include "server.h"

void		scale_to_percent(double * const tab, int size)
{
  int		total = 0;
  double	ratio;

  for (int i = 0; i < size; ++i)
    total += tab[i];
  ratio = total / 100.0;
  for (int i = 0; i < size; ++i)
    tab[i] /= ratio;
}

void		init_probs(double * const tab)
{
  tab[0] = PLINEMATE;
  tab[1] = PDERAUMERE;
  tab[2] = PSIBUR;
  tab[3] = PMENDIANE;
  tab[4] = PPHIRAS;
  tab[5] = PTHYSTAME;
}

void	generate_item(char * const box,
		      const double * const item_prob)
{
  int	start;
  int	randnum;

  start = 0;
  randnum = rand() % 100;
  if (rand() % 100 < POP_PROB)
    {
      for (int i = 0; i < NB_PROB; ++i)
	{
	  if (start + item_prob[i] > randnum)
	    {
	      *box = i;
	      break ;
	    }
	  start += item_prob[i];
	}
    }
  else
    *box = EMPTY;
}

int		generate_map(t_world *world)
{
  int		size;
  double	item_prob[NB_PROB];

  size = world->height * world->width;
  if ((world->map = malloc(size)) == NULL)
    return (iperror("generate_map: malloc", -1));
  init_probs(item_prob);
  scale_to_percent(item_prob, NB_PROB);
  for (int i = 0; i < size; ++i)
    generate_item(&world->map[i], item_prob);
  return (0);
}
