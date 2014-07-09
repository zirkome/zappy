/*
** geometry.c for geometry in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 28 16:36:28 2014 luc sinet
** Last update Sun Jun 29 13:43:57 2014 luc sinet
*/

#include <math.h>

double	point_distance(double ax, double ay, double bx, double by)
{
  return (sqrt(pow(ax - bx, 2) + pow(ay - by, 2)));
}

double	calc_director_coef(double ax, double ay, double bx, double by)
{
  return ((by - ay) / (bx - ax));
}

double	get_origin_coor(double ax, double ay, double dir_coef)
{
  return (ay - dir_coef * ax);
}
