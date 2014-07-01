/*
** connection.c for connection in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:12:56 2014 luc sinet
** Last update Tue Jul  1 16:33:39 2014 luc sinet
*/

#include "server.h"

int			connect_new_user(t_server *server)
{
  int			fd;
  struct sockaddr_in	client;
  socklen_t		size;
  t_client		*cl;

  size = sizeof(struct sockaddr_in);
  if ((fd = accept(server->fd, (struct sockaddr *)&client, &size)) == -1)
    return (iperror("accept", -1));
  if (add_user(&server->cl, &server->world, fd) == NULL)
    return (-1);
  cl = server->cl;
  while (cl->next)
    cl = cl->next;
  queue_push(&cl->queue, "BIENVENUE\n");
  return (fd);
}

void		erase_client(t_world *world, t_client *cl)
{
  int		pos;

  pos = MAP_POS(cl->player->x, cl->player->y, world->width);
  string_erase(world->map[pos], PLAYER);
  if (cl->player->teamptr != NULL)
    ++cl->player->teamptr->slots;
  queue_clear(&cl->queue);
  free(cl->rb->buf);
  free(cl->rb);
  free(cl->player);
  close(cl->fd);
  printf("Client disconnected\n");
}

int		kick_user(t_client **list, t_client *cl, t_world *world)
{
  t_client	*tmp;

  tmp = *list;
  if (tmp == cl)
    {
      *list = cl->next;
      erase_client(world, cl);
      return (2);
    }
  while (tmp->next && tmp->next != cl)
    tmp = tmp->next;
  if (tmp->next)
    {
      tmp->next = cl->next;
      erase_client(world, cl);
      return (2);
    }
  return (ierror("Can't disconnect client\n", -1));
}

int	disconnect_user(UNUSED t_server *server, t_client *cl)
{
  cl->ghost = true;
  return (0);
}
