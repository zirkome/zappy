/*
** broadcast_calculs.c for calc_broad in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 30 10:25:32 2014 luc sinet
** Last update Mon Jun 30 10:33:40 2014 luc sinet
*/

#include "server.h"

void	translate_point(t_geometry *geo, t_world *world, int dist)
{
  if ((dist = point_distance(geo->ax, geo->ay, geo->bx,
			     geo->by + world->height)) < geo->p_dist)
    {
      geo->p_dist = dist;
      geo->by += world->height;
    }
  else if ((dist = point_distance(geo->ax, geo->ay, geo->bx,
				  geo->by - world->height)) < geo->p_dist)
    {
      geo->p_dist = dist;
      geo->by -= world->height;
    }
  if ((dist = point_distance(geo->ax, geo->ay, geo->bx + world->width,
			     geo->by)) < geo->p_dist)
    {
      geo->p_dist = dist;
      geo->bx += world->width;
    }
  else if ((dist = point_distance(geo->ax, geo->ay, geo->bx - world->width,
				  geo->by)) < geo->p_dist)
    {
      geo->p_dist = dist;
      geo->bx -= world->width;
    }
}

int		find_case(t_geometry *geo, double *x, double *y)
{
  double	dist;
  double	tmp_dist;
  double	tx;
  double	ty;

  dist = -1;
  tx = (geo->bx + ((geo->bx > geo->ax) ? -GEO_STEP : GEO_STEP));
  ty = geo->by;
  dist = point_distance(geo->ax, geo->ay, tx, ty);
  *x = geo->bx;
  *y = (geo->by + ((geo->by > geo->ay) ? -GEO_STEP : GEO_STEP));
  tmp_dist = point_distance(geo->ax, geo->ay, *x, *y);
  if (dist < tmp_dist)
    {
      *x = tx;
      *y = ty;
      return (0);
    }
  return (1);
}

int		get_case_pos(double ax, double ay,
			     double x, double y)
{
  static	t_case tab[8] = {{0.5, -1.5},
				 {-0.5, -1.5},
				 {-0.5, -0.5},
				 {-0.5, 0.5},
				 {0.5, -0.5},
				 {1.5, 0.5},
				 {1.5, -0.5},
				 {1.5, -1.5}};
  int		i;

  for (i = 0; i < 8; ++i)
    {
      if (y > tab[i].by + ay && y < tab[i].by + 1 + ay &&
	  x > tab[i].bx - 1 + ax && x < tab[i].bx + ax)
	return (i + 1);
    }
  return (0);
}
