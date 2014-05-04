/*
** connection.c for connection in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:12:56 2014 luc sinet
** Last update Sat May  3 18:41:03 2014 luc sinet
*/

#include "server.h"

int			connect_new_user(t_serv *serv)
{
  int			fd;
  struct sockaddr_in	client;
  socklen_t		size;
  t_client		*cl;

  size = sizeof(struct sockaddr_in);
  if ((fd = accept(serv->fd, (struct sockaddr *)&client, &size)) == -1)
    return (iperror("connect_new_user: accept", -1));
  if (add_user(&serv->cl, fd) == -1)
    return (-1);
  cl = serv->cl;
  while (cl->next)
    cl = cl->next;
  queue_push(&cl->queue, "BIENVENUE\n");
  return (0);
}

void		erase_client(t_client *cl)
{
  printf("Client disconnected\n");
  free(cl->rb->buf);
  free(cl->rb);
  close(cl->fd);
}

int		disconnect_user(t_serv *serv, t_client *cl)
{
  t_client	*list;

  list = serv->cl;
  if (serv->cl == cl)
    {
      serv->cl = cl->next;
      erase_client(cl);
      return (2);
    }
  while (list->next && list->next != cl)
    list = list->next;
  if (list->next)
    {
      list->next = cl->next;
      erase_client(cl);
      return (2);
    }
  return (ierror("Can't disconnect client\n", -1));
}
