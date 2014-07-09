/*
** player_incantation.c for incant in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Wed Jul  2 18:22:49 2014 luc sinet
** Last update Wed Jul  9 12:13:51 2014 luc sinet
*/

#include "server.h"
#include "gui.h"

int		elevate_players(t_vector *vec, int num, int lev)
{
  t_client	*client;
  unsigned int	i;
  unsigned int	size;
  char		tab[64];

  size = vector_size(vec);
  for (i = 0; i < size && num > 0; ++i)
    {
      client = vector_get(vec, i);
      if (client->player->level == lev)
	{
	  snprintf(tab, sizeof(tab), "niveau actuel : %d\n",
		   client->player->level);
	  queue_push(&client->queue, tab);
	  client->player->level += 1;
	  --num;
	}
    }
  return (0);
}

t_vector	*check_incantation_conditions(t_server *server,
					      t_client *client)
{
  t_player	*pl;
  t_vector	*vec;
  int		num_player;

  pl = client->player;
  if (!enough_ressources(pl->level, pl->x, pl->y, &server->world))
    return (NULL);
  if ((vec = malloc(sizeof(t_vector))) == NULL)
    return (NULL);
  vector_init(vec);
  get_player_at_pos(vec, server->cl, pl->x, pl->y);
  if ((num_player = needed_same_level(pl->level) + 1) !=
      (num_same_level(vec, pl->level))
      || (int)vector_size(vec) != num_player)
    {
      vector_clear(vec);
      free(vec);
      return (NULL);
    }
  return (vec);
}

int		prepare_incantation(t_server *server, t_client *client)
{
  t_vector	*vec;

  if ((vec = check_incantation_conditions(server, client)) == NULL ||
      queue_push(&client->queue, "elevation en cours\n") == -1)
    {
      if (vec != NULL)
	{
	  vector_clear(vec);
	  free(vec);
	}
      queue_push(&client->queue, "ko\n");
      return (-1);
    }
  gui_events_handling(server, client, NULL, &gui_incantation_start);
  client->player->save_pos[0] = client->player->x;
  client->player->save_pos[1] = client->player->y;
  vector_clear(vec);
  free(vec);
  return (0);
}

t_vector       	*second_incantation_check(t_server *server, t_client *client)
{
  t_gui_arg	garg;
  t_vector	*vec;

  if ((vec = check_incantation_conditions(server, client)) == NULL ||
      (client->player->save_pos[0] != client->player->x) ||
      (client->player->save_pos[1] != client->player->y))
    {
      if (vec != NULL)
	{
	  vector_clear(vec);
	  free(vec);
	}
      queue_push(&client->queue, "ko\n");
      garg.id = 0;
      gui_events_handling(server, client, &garg, &gui_incantation_end);
      return (NULL);
    }
  return (vec);
}

int		pl_incantation(t_server *server, t_client *client,
			       char *arg UNUSED)
{
  char		tab[64];
  t_player	*pl;
  t_vector	*vec;
  unsigned int	num_player;
  t_gui_arg	garg;

  pl = client->player;
  if ((vec = second_incantation_check(server, client)) == NULL)
    return (-1);
  num_player = needed_same_level(pl->level);
  pl->level += 1;
  snprintf(tab, sizeof(tab), "niveau actuel : %d\n",
	   pl->level);
  elevate_players(vec, num_player - 1, pl->level);
  vector_clear(vec);
  free(vec);
  reassign_ressources(pl->level - 1, pl->x, pl->y, &server->world);
  garg.id = 1;
  gui_events_handling(server, client, &garg, &gui_incantation_end);
  return (queue_push(&client->queue, tab));
}
