/*
** pars.c for pars in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:46:12 2014 luc sinet
** Last update Tue Jun 17 18:45:08 2014 luc sinet
*/

#include "server.h"

static	t_command	g_command[] =
{
  {"avance", NULL},
  {"droite", NULL},
  {"gauche", NULL},
  {"voir", NULL},
  {"inventaire", NULL},
  {"prend", NULL},
  {"pose", NULL},
  {"expulse", NULL},
  {"broadcast", NULL},
  {"incantation", NULL},
  {"fork", NULL},
  {"connect_nbr", NULL}
};

int	parse_msg(t_server *server, t_client *cl, char *cmd)
{
  (void)server;
  (void)cl;
  write(1, "Got message ", strlen("Got message "));
  write(1, cmd, strlen(cmd));
  write(1, "\n", 1);
  return (0);
}
