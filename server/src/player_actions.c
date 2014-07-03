/*
** player_actions.c for actions in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 20 13:50:31 2014 luc sinet
** Last update Thu Jul  3 18:12:51 2014 luc sinet
*/

#include "server.h"

int		pl_take(t_server *server, t_client *client,
			char *arg)
{
  t_player	*pl;
  int		elem_id;
  int		pos;

  pl = client->player;
  pos = MAP_POS(pl->x, pl->y, server->world.width);
  if ((elem_id = get_element_id(arg)) == -1 ||
      elem_id >= PLAYER ||
      string_erase(server->world.map[pos], elem_id) == -1 ||
      add_to_inventory(pl, elem_id, 1) == -1)
    {
      queue_push(&client->queue, "ko\n");
      return (-1);
    }
  queue_push(&client->queue, "ok\n");
  return (0);
}

int		pl_put(t_server *server, t_client *client,
		       char *arg)
{
  t_player	*pl;
  int		elem_id;

  pl = client->player;
  if ((elem_id = get_element_id(arg)) == -1 ||
      remove_from_inventory(pl, elem_id, 1) == -1 ||
      add_to_world(&server->world, elem_id, pl->x, pl->y))
    {
      queue_push(&client->queue, "ko\n");
      return (-1);
    }
  queue_push(&client->queue, "ok\n");
  return (0);
}

void		expulse_player(t_world *world, t_client *client, t_dir dir)
{
  char		tab[32];
  t_player	*pl;
  int		fdir;
  double       	oldx;
  double	oldy;

  pl = client->player;
  oldx = pl->x + 0.5;
  oldy = pl->y + 0.5;
  remove_from_world(world, PLAYER, pl->x, pl->y);
  pl->x += ((dir == WEST) ? -1 : (dir == EAST) ? 1 : 0);
  pl->y += ((dir == SOUTH) ? 1 : (dir == NORTH) ? -1 : 0);
  fdir = get_case_pos((double)pl->x + 0.5, (double)pl->y + 0.5, oldx, oldy);
  if (fdir != 0)
    {
      fdir = (fdir + client->player->dir * 2);
      fdir = (fdir > 8) ? (fdir - 8) : fdir;
    }
  apply_map_looping(&pl->x, &pl->y, world->width, world->height);
  add_to_world(world, PLAYER, pl->x, pl->y);
  snprintf(tab, sizeof(tab), "deplacement: %d\n", fdir);
  queue_push(&client->queue, tab);
}

int		pl_expulse(t_server *server, t_client *client,
			   char *arg UNUSED)
{
  int		to_expulse;
  t_node	*tmp;

  to_expulse = count_type_on_box(&server->world, PLAYER,
				 client->player->x, client->player->y) - 1;
  if (to_expulse > 0)
    {
      for (tmp = server->cl; tmp != NULL && to_expulse > 0; tmp = tmp->next)
	{
	  if (((t_client*)tmp->value) != client &&
	      ((t_client*)tmp->value)->player->x == client->player->x &&
	      ((t_client*)tmp->value)->player->y == client->player->y)
	    {
	      expulse_player(&server->world, ((t_client*)tmp->value), client->player->dir);
	      --to_expulse;
	    }
	}
      return (queue_push(&client->queue, "ok\n"));
    }
  else
    return (queue_push(&client->queue, "ko\n"));
  return (0);
}
