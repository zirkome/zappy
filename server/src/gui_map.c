/*
** gui_map.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jun 24 13:18:45 2014 guillaume fillon
** Last update Mon Jun 30 15:09:52 2014 guillaume fillon
*/

#include "server.h"

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

int	gui_msz(t_server *server, t_client *client, UNUSED char *arg)
{
  char	*msg;

  msg = cnprintf(15, "msz %d %d\n", server->world.width, server->world.height);
  queue_push(&client->queue, msg);
  free(msg);
  return (0);
}

int	gui_bct(UNUSED t_server *server, UNUSED t_client *client, UNUSED char *arg)
{
  return (0);
}

int		gui_mct(t_server *server, t_client *client, UNUSED char *arg)
{
  char		*msg;
  int		i;
  int		x;
  int		y;
  int		width;
  int		height;
  t_string	**map;

  width = server->world.width;
  height = server->world.height;
  map = server->world.map;
  for (i = 0; i < width * height; ++i)
    {
      x = i % width;
      y = i / width;
      msg = cnprintf(BUFSIZ, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
		     count_resource(map[i], FOOD),
		     count_resource(map[i], LINEMATE),
		     count_resource(map[i], DERAUMERE),
		     count_resource(map[i], SIBUR),
		     count_resource(map[i], MENDIANE),
		     count_resource(map[i], PHIRAS),
		     count_resource(map[i], THYSTAME));
      queue_push(&client->queue, msg);
      free(msg);
    }
  return (0);
}

int		gui_tna(t_server *server, t_client *client, UNUSED char *arg)
{
  int		i;
  char		*msg;
  t_team	*teams;

  teams = server->world.teams;
  for (i = 0; i < server->world.nb_teams; ++i)
    {
      msg = cnprintf(BUFSIZ, "tna %s\n", teams[i].name);
      queue_push(&client->queue, msg);
      free(msg);
    }
  return (0);
}
