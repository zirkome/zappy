/*
** player_broadcast.c for broadcast in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:40:26 2014 luc sinet
** Last update Mon Jul  7 15:10:19 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

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
  if (pos != 0)
    {
      pos = (pos + client->player->dir * 2);
      pos = (pos > 8) ? (pos - 8) : pos;
    }
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
  if (geo.ax == geo.bx && geo.ay != geo.by)
    geo.bx += 0.1;
  geo.a = calc_director_coef(geo.ax, geo.ay, geo.bx, geo.by);
  geo.b = get_origin_coor(geo.ax, geo.ay, geo.a);
  return (send_broadcast(&geo, client, arg));
}

int		pl_broadcast(t_server *server, t_client *client,
			     char *arg)
{
  t_gui_arg	garg;
  t_player	*pl;
  t_node	*tmp;

  pl = client->player;
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    if ((t_client*)tmp->value != client)
      find_player_dir(pl, (t_client*)tmp->value, &server->world, arg);
  garg.msg = arg;
  gui_events_handling(server, client, &garg, &gui_broadcast);
  return (queue_push(&client->queue, "ok\n"));
}
