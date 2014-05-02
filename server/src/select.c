/*
** select.c for select in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Apr 20 08:36:48 2014 luc sinet
** Last update Fri May  2 22:18:23 2014 luc sinet
*/

#include "server.h"

int	user_read(t_serv *serv, t_client *cl)
{
  (void)serv;
  (void)cl;
  return (0);
}

int	user_write(t_serv *serv, t_client *cl)
{
  (void)serv;
  (void)cl;
  return (0);
}

int		read_state(t_serv *serv)
{
  t_client	*tmp;
  int		ret;

  (void)ret;
  tmp = serv->cl;
  if (FD_ISSET(serv->fd, &serv->r_fd))
    connect_new_user(serv);
  while (tmp)
    {
      ret = 0;
      if (FD_ISSET(tmp->fd, &serv->r_fd))
	ret = user_read(serv, tmp);
      tmp = tmp->next;
    }
  return (0);
}

int		write_state(t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->cl;
  while (tmp)
    {
      if (FD_ISSET(tmp->fd, &serv->w_fd))
	user_write(serv, tmp);
      tmp = tmp->next;
    }
  return (0);
}
