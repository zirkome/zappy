/*
** handle_user.c for handle in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 12:29:40 2014 luc sinet
** Last update Wed Jul  9 15:12:20 2014 guillaume fillon
*/

#include "scheduler.h"
#include "server.h"

static int	g_increment = 1;

static int	init_player(t_client *new)
{
  if ((new->player = malloc(sizeof(t_player))) == NULL)
    return (iperror("init_player: malloc", -1));
  new->player->dir = rand() % 4;
  new->player->x = 0;
  new->player->y = 0;
  new->player->level = 1;
  new->player->id = g_increment++;
  new->player->teamptr = NULL;
  new->player->jobs = NULL;
  new->player->foodjob = NULL;
  memset(new->player->inventory, 0, sizeof(new->player->inventory));
  memset(new->player->save_pos, 0, sizeof(new->player->save_pos));
  new->player->inventory[FOOD - 1] = INITFOOD;
  return (0);
}

static void	init_client(t_client *client, int fd)
{
  client->fd = fd;
  client->ghost = false;
  client->type = UNKNOWN;
  client->queue = queue_init();
}

t_client	*client_new(int fd)
{
  t_client	*new;

  if ((new = malloc(sizeof(t_client))) == NULL)
    return (ptperror("client_new: malloc", NULL));
  else if ((new->rb = create_ringbuffer(1024)) == NULL ||
	   init_player(new) == -1)
    {
      free(new);
      return (NULL);
    }
  init_client(new, fd);
  return (new);
}

void		erase_client(t_world *world, t_client *cl)
{
  if ((cl->type == (t_client_type)IA || cl->type == (t_client_type)EGG)
      && cl->player->teamptr != NULL)
    remove_from_world(world, PLAYER, cl->player->x,
		      cl->player->y);
  if (cl->player->teamptr != NULL && cl->type != EGG)
    ++cl->player->teamptr->slots;
  queue_clear(&cl->queue);
  if (cl->player != NULL)
    {
      free(cl->player->foodjob);
      list_clear(&cl->player->jobs, &free_job);
    }
  free_ringbuffer(cl->rb);
  free(cl->player);
  if (cl->type != EGG)
    close(cl->fd);
  printf("Client disconnected\n");
}
