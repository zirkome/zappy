/*
** init.c for init in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 09:39:44 2014 luc sinet
** Last update Tue Jul  1 18:09:25 2014 luc sinet
*/

#include <signal.h>
#include "server.h"
#include "egg.h"

static void	init_teams_slots(t_server *server)
{
  int		i;
  t_world	w;

  w = server->world;
  for (i = 0; i < w.nb_teams; ++i)
    w.teams[i].slots = w.slots;
}

int		init_server(t_server *server)
{
  if (server->world.nb_teams < 2)
    {
      fputs("You must precise two teams name minimum with -n option" \
	    "(e.g: -n team1 team2)\n", stderr);
      return (-1);
    }
  if (server->world.port == NULL)
    server->world.port = DEFAULT_PORT;
  if ((server->fd = create_inet_server_socket(NULL, server->world.port)) < 0)
    return (-1);
  if (server->world.delay == 0)
    server->world.delay = 100;
  if (server->world.slots == 0)
    server->world.slots = 1;
  server->cl = NULL;
  srand(time(NULL));
  init_teams_slots(server);
  if ((server->world.egg = malloc(sizeof(t_egg))) == NULL ||
      generate_map(&server->world) == -1)
    return (-1);
  vector_init(server->world.egg);
  welcome_server(server->world.port);
  return (0);
}
