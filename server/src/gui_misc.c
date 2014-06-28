/*
** gui_misc.c for project in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 26 21:14:01 2014 guillaume fillon
** Last update Thu Jun 26 22:09:08 2014 guillaume fillon
*/

#include "server.h"

int	gui_welcome(t_server *server, t_client *client)
{
  int	ret;

  ret = gui_msz(server, client, NULL);
  ret |= gui_sgt(server, client, NULL);
  ret |= gui_mct(server, client, NULL);
  ret |= gui_tna(server, client, NULL);
  return (ret);
}
