/*
** gui_take.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 14:45:49 2014 guillaume fillon
** Last update Mon Jul  7 11:31:31 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

static int	count_resource(t_string *square, int res)
{
  int		count;
  int		i;

  count = 0;
  for (i = 0; square->content[i] != '\0'; ++i)
    if (square->content[i] == res)
      count++;
  return (count);
}

int		gui_take(t_server *server, t_client *graphic,
			 t_client *client, t_gui_arg *arg)
{
  int		i;
  t_string	**map;
  t_player	*pl;

  map = server->world.map;
  pl = client->player;
  i = MAP_POS(pl->x, pl->y, server->world.width);
  queue_push_message(&graphic->queue, "pgt %d %d\n", pl->id, arg->id);
  queue_push_message(&graphic->queue, "pin %d %d %d %d %d %d %d %d %d %d\n",
		     pl->id, pl->x, pl->y,
		     pl->inventory[0], pl->inventory[1],
		     pl->inventory[2], pl->inventory[3],
		     pl->inventory[4], pl->inventory[5],
		     pl->inventory[6]);
  queue_push_message(&graphic->queue,
		     "bct %d %d %d %d %d %d %d %d %d\n",
		     pl->x, pl->y,
		     count_resource(map[i], FOOD),
		     count_resource(map[i], LINEMATE),
		     count_resource(map[i], DERAUMERE),
		     count_resource(map[i], SIBUR),
		     count_resource(map[i], MENDIANE),
		     count_resource(map[i], PHIRAS),
		     count_resource(map[i], THYSTAME));
  return (0);
}
