/*
** pars.c for pars in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:46:12 2014 luc sinet
** Last update Fri May  2 23:13:24 2014 luc sinet
*/

#include "server.h"

int	pars_msg(t_serv *serv, t_client *cl, char *cmd)
{
  (void)serv;
  (void)cl;
  write(1, "Got message ", strlen("Got message "));
  write(1, cmd, strlen(cmd));
  write(1, "\n", 1);
  return (0);
}
