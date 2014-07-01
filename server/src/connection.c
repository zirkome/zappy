/*
** connection.c for connection in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:12:56 2014 luc sinet
** Last update Tue Jul  1 18:31:20 2014 guillaume fillon
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
  cl = client_new(fd);
  if (cl == NULL)
    return (-1);
  list_add_elem_at_back(&server->cl, cl);
  add_to_world(&server->world, PLAYER, cl->player->x, cl->player->y);
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

int		kick_user(t_list *list, t_client *cl, t_world *world)
{
  erase_client(world, cl);
  list_del_node(list, cl);
  return (2);
}

int	disconnect_user(UNUSED t_server *server, t_client *cl)
{
  cl->ghost = true;
  return (0);
}
