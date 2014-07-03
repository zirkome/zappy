/*
** player_incantation.c for incant in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Wed Jul  2 18:22:49 2014 luc sinet
** Last update Thu Jul  3 11:23:23 2014 luc sinet
*/

#include "server.h"

int		get_ent_amount(int x, int y, int type, t_world *world)
{
  int		pos;
  int		i;
  int		counter;
  t_string	*box;

  counter = 0;
  pos = MAP_POS(x, y, world->width);
  box = world->map[pos];
  if (box->content == NULL)
    return (0);
  for (i = 0; box->content[i]; ++i)
    if (box->content[i] == type)
      ++counter;
  return (counter);
}

t_bool		enough_ressources(int lev, int x, int y, t_world *world)
{
  static int	ressources[7][7] = {
    {1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {2, 0, 1, 0, 2, 0},
    {1, 1, 2, 0, 1, 0},
    {1, 2, 1, 3, 0, 0},
    {1, 2, 3, 0, 1, 0},
    {2, 2, 2, 2, 2, 1}
  };
  int		i;

  if (lev >= 8)
    return (false);
  for (i = 0; i < 7; ++i)
    if (ressources[lev - 1][i] > get_ent_amount(x, y, i + LINEMATE, world))
      return (false);
  return (true);
}

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
	  snprintf(tab, sizeof(tab), "elevation en cours niveau actuel : %d\n",
		   client->player->level);
	  queue_push(&client->queue, tab);
	  client->player->level += 1;
	  --num;
	}
    }
  return (0);
}

int		pl_incantation(t_server *server, t_client *client,
			       char *arg UNUSED)
{
  t_player	*pl;
  t_vector	vec;
  char		tab[64];
  int		num_player;

  pl = client->player;
  vector_init(&vec);
  if (!enough_ressources(pl->level, pl->x, pl->y, &server->world))
    return (-1);
  get_player_at_pos(&vec, server->cl, pl->x, pl->y);
  if ((num_player = needed_same_level(pl->level)) >
      num_same_level(&vec, client->player->level))
    {
      vector_clear(&vec);
      return (-1);
    }
  snprintf(tab, sizeof(tab), "elevation en cours niveau actuel : %d\n",
	   client->player->level);
  client->player->level += 1;
  elevate_players(&vec, num_player - 1, client->player->level);
  vector_clear(&vec);
  return (queue_push(&client->queue, tab));
}
