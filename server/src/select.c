/*
** select.c for select in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Apr 20 08:36:48 2014 luc sinet
** Last update Sat May  3 17:18:22 2014 luc sinet
*/

#include "server.h"

int		user_read(t_serv *serv, t_client *cl)
{
  char		buf[RSIZE];
  char		aligned[cl->rb->size + 1];
  char		*tmp;
  ssize_t	retv;

  tmp = aligned;
  if ((retv = read(cl->fd, buf, RSIZE)) <= 0)
    return (disconnect_user(serv, cl));
  fill_ringbuffer(cl->rb, buf, retv);
  align_ringbuffer(cl->rb, aligned, sizeof(aligned));
  while ((retv = get_char_pos(cl->rb, tmp, '\n')) != -1)
    {
      tmp[retv] = '\0';
      pars_msg(serv, cl, tmp);
      tmp = &tmp[retv + 1];
    }
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
  t_client	*tofree;
  int		ret;

  tmp = serv->cl;
  if (FD_ISSET(serv->fd, &serv->r_fd))
    connect_new_user(serv);
  while (tmp)
    {
      ret = 0;
      if (FD_ISSET(tmp->fd, &serv->r_fd))
	ret = user_read(serv, tmp);
      if (ret == DISCONNECTED)
	tofree = tmp;
      tmp = tmp->next;
      if (ret == DISCONNECTED)
	free(tofree);
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
