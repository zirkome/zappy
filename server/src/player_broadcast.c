/*
** player_broadcast.c for broadcast in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:40:26 2014 luc sinet
** Last update Sun Jun 29 23:59:23 2014 luc sinet
*/

#include "geometry.h"
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

int		send_broadcast(t_geometry *geo, t_client *client, char *arg)
{
  /* char		tab[64]; */
  int		pos;
  double	x;
  double	y;

  if (find_case(geo, &x, &y) == 0)
    y = (geo->a * x + geo->b);
  else
    x = ((y - geo->b) / geo->a);
  pos = get_case_pos(geo->bx, geo->by, x, y);
  pos = (pos + client->player->dir * 2) % 9;
  //  snprintf(tab, 64, "message %d,", pos);
  return (0);
}

int		find_player_dir(t_player *pla, t_client *client,
				t_world *world, char *arg)
{
  t_geometry	geo;
  t_player	*plb;

  plb = client->player;
  geo.ax = pla->x + 0.5;
  geo.ay = pla->y + 0.5;
  geo.bx = plb->x + 0.5;
  geo.by = plb->y + 0.5;
  geo.p_dist = point_distance(geo.ax, geo.ay, geo.bx, geo.by);
  translate_point(&geo, world, 0);
  geo.a = calc_director_coef(geo.ax, geo.ay, geo.bx, geo.by);
  geo.b = get_origin_coor(geo.ax, geo.ay, geo.a);
  return (send_broadcast(&geo, client, arg));
}

int		pl_broadcast(t_server *server, t_client *client,
			     char *arg)
{
  t_player	*pl;
  t_client	*tmp;

  pl = client->player;
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    if (tmp != client)
      find_player_dir(pl, tmp, &server->world, arg);
  return (0);
}
