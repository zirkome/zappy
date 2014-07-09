/*
** select.c for select in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Apr 20 08:36:48 2014 luc sinet
** Last update Wed Jul  9 17:48:10 2014 luc sinet
*/

#include "server.h"

int		user_read(t_server *server, t_client *cl)
{
  char		buf[RSIZE];
  char		aligned[cl->rb->size + 1];
  char		*tmp;
  char		*save;
  ssize_t	retv;

  tmp = aligned;
  if ((retv = read(cl->fd, buf, RSIZE)) <= 0)
    return (disconnect_user(server, cl));
  fill_ringbuffer(cl->rb, buf, retv);
  if ((tmp = get_buff(cl->rb)) == NULL)
    return (-1);
  save = tmp;
  while ((retv = get_char_pos(tmp, '\n')) != -1)
    {
      tmp[retv] = '\0';
      if (process_input(server, cl, tmp) < -1)
	{
	  queue_push(&cl->queue, "ko\n");
	  return (disconnect_user(server, cl));
	}
      tmp = &tmp[retv + 1];
    }
  update_ringbuffer(cl->rb, save, tmp);
  return (0);
}

int	read_state(t_server *server, t_client *client)
{
  user_read(server, client);
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
    {
      perror("");
      return (disconnect_user(server, cl));
    }
  if (wsize < msglen)
    shift_msg(msg, wsize);
  else
    queue_pop(&cl->queue);
  return (0);
}

int	write_state(t_server *server, t_client *client)
{
  if (queue_empty(client->queue))
    return (-1);
  user_write(server, client);
  return (0);
}
