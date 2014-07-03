/*
** incantation_ressources.c for incantation_ressources in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Jul  3 11:39:23 2014 luc sinet
** Last update Thu Jul  3 20:50:56 2014 luc sinet
*/

#include "server.h"

int		*get_needed_ressources(int lev)
{
  static int	ressources[7][7] = {
    {1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0},
    {1, 1, 2, 0, 1, 0},
    {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0},
    {2, 2, 2, 2, 2, 1}
  };

  return ((lev >= 8 || lev < 1) ? NULL : ressources[lev - 1]);
}

int		get_ent_amount(int x, int y, int type, t_world *world)
{
  int		pos;
  int		i;
  int		counter;
  t_string	*box;

  counter = 0;
  pos = MAP_POS(x, y, world->width);
  box = world->map[pos];
  if (box->content == NULL)
    return (0);
  for (i = 0; box->content[i]; ++i)
    if (box->content[i] == type)
      ++counter;
  return (counter);
}

t_bool	enough_ressources(int lev, int x, int y, t_world *world)
{
  int	i;
  int	*ressources;

  if ((ressources = get_needed_ressources(lev)) == NULL)
    return (false);
  for (i = 0; i < 6; ++i)
    {
      printf("%d %d\n", ressources[i], get_ent_amount(x, y, i + LINEMATE, world));
      if (ressources[i] != get_ent_amount(x, y, i + LINEMATE, world))
	return (false);
    }
  return (true);
}

void	reassign_ressources(int lev, int x, int y, t_world *world)
{
  int	*ressources;
  int	i;
  int	j;

  if ((ressources = get_needed_ressources(lev)) == NULL)
    return ;
  for (i = 0; i < 7; ++i)
    {
      for (j = 0; j < ressources[i]; ++j)
	{
	  remove_from_world(world, i + LINEMATE, x, y);
	  add_to_world(world, i + LINEMATE, rand() % world->width,
		       rand() % world->height);
	}
    }
}
