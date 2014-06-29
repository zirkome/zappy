/*
** player_broadcast.c for broadcast in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:40:26 2014 luc sinet
** Last update Sun Jun 29 13:44:54 2014 luc sinet
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

int		find_player_dir(t_player *pla, t_player *plb, t_world *world)
{
  t_geometry	geo;

  geo.ax = pla->x;
  geo.ay = pla->y;
  geo.bx = plb->x;
  geo.by = plb->y;
  geo.p_dist = point_distance(geo.ax, geo.ay, geo.bx, geo.by);
  translate_point(&geo, world, 0);
  geo.a = calc_director_coef(geo.ax, geo.ay, geo.bx, geo.by);
  geo.b = get_origin_coor(geo.ax, geo.ay, geo.a);
  printf("A[%f, %f], B[%f, %f], y = %fx + %f\n",
	 geo.ax, geo.ay, geo.bx, geo.by, geo.a, geo.b);
  return (0);
}

int		pl_broadcast(t_server *server, t_client *client,
			     char *arg)
{
  t_player	*pl;
  t_client	*tmp;

  pl = client->player;
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    if (tmp != client)
      find_player_dir(pl, tmp->player, &server->world);
  return (0);
}
