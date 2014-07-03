/*
** geometry.h for geometry in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 28 18:02:43 2014 luc sinet
** Last update Mon Jun 30 10:33:14 2014 luc sinet
*/

#ifndef _GEOMETRY_H_
# define _GEOMETRY_H_

# define GEO_STEP 1.499998

typedef struct	s_geometry
{
  double	ax;
  double	ay;
  double	bx;
  double	by;
  double	p_dist;
  double	a;
  double	b;
}		t_geometry;

typedef	struct	s_case
{
  double	bx;
  double	by;
}		t_case;

double	point_distance(double ax, double ay, double bx, double by);
double	calc_director_coef(double ax, double ay, double bx, double by);
double	get_origin_coor(double ax, double ay, double dir_coef);

#endif /* _GEOMETRY_H_ */
