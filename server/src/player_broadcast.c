/*
** player_broadcast.c for broadcast in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:40:26 2014 luc sinet
** Last update Mon Jun 30 11:30:08 2014 luc sinet
*/

#include "server.h"

int		send_broadcast(t_geometry *geo, t_client *client, char *arg)
{
  char		tab[64];
  t_string	string;
  int		pos;
  double	x;
  double	y;
  int		ret;

  string_init(&string);
  if (find_case(geo, &x, &y) == 0)
    y = (geo->a * x + geo->b);
  else
    x = ((y - geo->b) / geo->a);
  pos = get_case_pos(geo->bx, geo->by, x, y);
  pos = (pos + client->player->dir * 2);
  pos = (pos > 8) ? (pos - 8) : pos;
  snprintf(tab, 64, "message %d,", pos);
  string_append(&string, tab, ALLOC_SIZE);
  string_append(&string, arg, ALLOC_SIZE);
  if ((ret = queue_push(&client->queue, string.content)) == 0)
    ret = queue_append_back(&client->queue, "\n");
  free(string.content);
  return (ret);
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
  return (queue_push(&client->queue, "ok\n"));
}
