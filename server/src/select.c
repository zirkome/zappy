/*
** select.c for select in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Apr 20 08:36:48 2014 luc sinet
** Last update Wed Jun 18 13:37:02 2014 luc sinet
*/

#include "server.h"

int		user_read(t_server *server, t_client *cl)
{
  char		buf[RSIZE];
  char		aligned[cl->rb->size + 1];
  char		*tmp;
  ssize_t	retv;

  tmp = aligned;
  if ((retv = read(cl->fd, buf, RSIZE)) <= 0)
    return (disconnect_user(server, cl));
  fill_ringbuffer(cl->rb, buf, retv);
  align_ringbuffer(cl->rb, aligned, sizeof(aligned));
  while ((retv = get_char_pos(cl->rb, tmp, '\n')) != -1)
    {
      tmp[retv] = '\0';
      process_input(server, cl, tmp);
      tmp = &tmp[retv + 1];
    }
  return (0);
}

int		user_write(t_server *server, t_client *cl)
{
  ssize_t	wsize;
  ssize_t	msglen;
  char		*msg;

  msg = queue_front(cl->queue);
  msglen = strlen(msg);
  if ((wsize = write(cl->fd, msg, msglen)) <= 0)
    return (disconnect_user(server, cl));
  if (wsize < msglen)
    shift_msg(msg, wsize);
  else
    queue_pop(&cl->queue);
  return (0);
}

int		read_state(t_server *server)
{
  t_client	*tmp;
  t_client	*tofree;
  int		ret;

  tmp = server->cl;
  if (FD_ISSET(server->fd, &server->r_fd))
    connect_new_user(server);
  while (tmp)
    {
      ret = 0;
      if (FD_ISSET(tmp->fd, &server->r_fd))
	ret = user_read(server, tmp);
      if (ret == DISCONNECTED)
	tofree = tmp;
      tmp = tmp->next;
      if (ret == DISCONNECTED)
	free(tofree);
    }
  return (0);
}

int		write_state(t_server *server)
{
  t_client	*tmp;
  t_client	*tofree;
  int		ret;

  tmp = server->cl;
  while (tmp)
    {
      ret = 0;
      if (FD_ISSET(tmp->fd, &server->w_fd))
	ret = user_write(server, tmp);
      if (ret == DISCONNECTED)
	tofree = tmp;
      tmp = tmp->next;
      if (ret == DISCONNECTED)
	free(tofree);
    }
  return (0);
}
