/*
** gui_incantation_start.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 16:00:35 2014 guillaume fillon
** Last update Tue Jul  8 12:28:58 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

int		gui_incantation_end(t_server *server, t_client *graphic,
				    t_client *client, UNUSED t_gui_arg *arg)
{
  t_node	*tmp;
  t_player	*pl;

  pl = client->player;
  queue_push_message(&graphic->queue, "pie %d %d %d\n",
		     pl->x, pl->y, arg->id);
  for (tmp = server->cl; tmp != NULL; tmp = tmp->next)
    {
      if (((t_client*)tmp->value)->type == IA)
	{
	  queue_push_message(&graphic->queue, "plv %d %d\n",
			     ((t_client*)tmp->value)->player->id,
			     ((t_client*)tmp->value)->player->level);
	}
    }
  gui_mct(server, graphic, NULL);
  return (0);
}

int		gui_incantation_start(t_server *server, t_client *graphic,
				      t_client *client, UNUSED t_gui_arg *arg)
{
  t_player	*pl;
  t_client	*cl;
  t_vector	vec;
  int		level;
  unsigned int	i;
  unsigned int	size;

  pl = client->player;
  level = pl->level;
  queue_push_message(&graphic->queue, "pic %d %d %d",
		     pl->x, pl->y, pl->level + 1);
  vector_init(&vec);
  get_player_at_pos(&vec, server->cl, pl->x, pl->y);
  size = vector_size(&vec);
  for (i = 0; i < size; ++i)
    {
      cl = vector_get(&vec, i);
      pl = cl->player;
      if (cl->type == IA && pl->level == level)
	queue_push_message(&graphic->queue, " %d", pl->id);
    }
  queue_push(&graphic->queue, "\n");
  vector_clear(&vec);
  return (0);
}
