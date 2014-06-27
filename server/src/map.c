/*
** map.c for map in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Jun 22 20:33:00 2014 luc sinet
** Last update Fri Jun 27 16:58:35 2014 luc sinet
*/

#include "server.h"

void		scale_to_percent(double * const tab, int size)
{
  int		total;
  int		i;
  double	ratio;

  total = 0;
  for (i = 0; i < size; ++i)
    total += tab[i];
  ratio = total / 100.0;
  if (ratio == 0)
    return ;
  for (i = 0; i < size; ++i)
    tab[i] /= ratio;
}

void		init_probs(double * const item, double * const drop)
{
  item[0] = PLINEMATE;
  item[1] = PDERAUMERE;
  item[2] = PSIBUR;
  item[3] = PMENDIANE;
  item[4] = PPHIRAS;
  item[5] = PTHYSTAME;
  drop[0] = PFIRST_CASE;
  drop[1] = PSECOND_CASE;
  drop[2] = PTHIRD_CASE;
  drop[3] = PFOURTH_CASE;
  drop[4] = PFIFTH_CASE;
}

int	generate_item(const double * const item_prob, int prob_size)
{
  int	start;
  int	randnum;
  int	i;

  start = 0;
  randnum = rand() % 101;
  for (i = 0; i < prob_size; ++i)
    {
      if (start + item_prob[i] > randnum)
	return (i + 1);
      start += item_prob[i];
    }
  return (1);
}

int		generate_boxes(t_string **box,
			       const double * const case_prob,
			       const double * const item_prob)
{
  t_string	*string;
  char		item[2];
  int		nb_obj;
  int		i;

  item[1] = '\0';
  nb_obj = generate_item(case_prob, CASE_PROB);
  if ((string = malloc(sizeof(t_string))) == NULL)
    return (-1);
  string_init(string);
  for (i = 0; i < nb_obj; --nb_obj)
    {
      item[0] = generate_item(item_prob, ITEM_PROB);
      if (string_append(string, item, AV_MAP) == NULL)
	return (-1);
    }
  *box = string;
  return (0);
}

int		generate_map(t_world *world)
{
  double	item_prob[ITEM_PROB];
  double	case_prob[CASE_PROB];
  int		map_size;
  int		i;

  map_size = world->height * world->width;
  if ((world->map = malloc(map_size * sizeof(t_string *))) == NULL)
    return (iperror("generate_map: malloc", -1));
  init_probs(item_prob, case_prob);
  scale_to_percent(item_prob, ITEM_PROB);
  scale_to_percent(case_prob, CASE_PROB);
  for (i = 0; i < map_size; ++i)
    {
      if (generate_boxes(&world->map[i], case_prob, item_prob) == -1)
	return (-1);
    }
  return (0);
}
