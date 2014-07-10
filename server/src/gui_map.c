/*
** gui_map.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jun 24 13:18:45 2014 guillaume fillon
** Last update Wed Jul  9 15:11:27 2014 guillaume fillon
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

int		gui_bct(t_server *server, t_client *client, char *arg)
{
  int		x;
  int		y;
  t_string	*line;
  char		*x_str;
  char		*y_str;

  x_str = strtok(arg, " \t");
  y_str = strtok(NULL, " \t");
  if (x_str == NULL || y_str == NULL)
    {
      queue_push(&client->queue, "sbp\n");
      return (-1);
    }
  x = stoi(x_str);
  y = stoi(y_str);
  line = server->world.map[y * server->world.width + x];
  queue_push_message(&client->queue, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
		     count_resource(line, FOOD), count_resource(line, LINEMATE),
		     count_resource(line, DERAUMERE),
		     count_resource(line, SIBUR),
		     count_resource(line, MENDIANE),
		     count_resource(line, PHIRAS),
		     count_resource(line, THYSTAME));
  return (0);
}

int		gui_mct(t_server *server, t_client *client, UNUSED char *arg)
{
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
      queue_push_message(&client->queue, "bct %d %d %d %d %d %d %d %d %d\n",
			 x, y,
			 count_resource(map[i], FOOD),
			 count_resource(map[i], LINEMATE),
			 count_resource(map[i], DERAUMERE),
			 count_resource(map[i], SIBUR),
			 count_resource(map[i], MENDIANE),
			 count_resource(map[i], PHIRAS),
			 count_resource(map[i], THYSTAME));
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
