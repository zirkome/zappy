/*
** geometry.h for geometry in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 28 18:02:43 2014 luc sinet
** Last update Sun Jun 29 13:28:32 2014 luc sinet
*/

#ifndef _GEOMETRY_H_
# define _GEOMETRY_H_

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

double	point_distance(double ax, double ay, double bx, double by);
double	calc_director_coef(double ax, double ay, double bx, double by);
double	get_origin_coor(double ax, double ay, double dir_coef);

#endif /* _GEOMETRY_H_ */
