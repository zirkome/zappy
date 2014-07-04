/*
** player_inventory.c for inventory in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 27 21:42:58 2014 luc sinet
** Last update Fri Jul  4 11:30:22 2014 luc sinet
*/

#include "server.h"

int	add_to_inventory(t_player *player, int type, int amount)
{
  if (type <= 0 || type >= PLAYER)
    return (-1);
  player->inventory[type - 1] += amount;
  return (0);
}

int	remove_from_inventory(t_player *player, int type, int amount)
{
  if (type < FOOD || type > THYSTAME || player->inventory[type - 1] == 0)
    return (-1);
  player->inventory[type - 1] -= amount;
  return (0);
}

int	get_inventory_amount_type(t_player *player, int type)
{
  if (type <= 0 || type >= NB_ELEM)
    return (-1);
  return (player->inventory[type - 1]);
}

int		list_player_inventory(t_string *string, t_player *player,
				      int id)
{
  char		tab[32];
  char		*elem;
  int		amount;

  if ((elem = get_name_from_id(id + 1)) == NULL ||
      string_append(string, elem, ALLOC_SIZE) == NULL ||
      (amount = get_inventory_amount_type(player, id + 1)) == -1)
    return (-1);
  free(elem);
  if (id + 1 < ITEM_PROB)
    snprintf(tab, 31, " %d, ", amount);
  else
    snprintf(tab, 31, " %d", amount);
  return (string_append(string, tab, ALLOC_SIZE) == NULL ? -1 : 0);
}

int		pl_inventory(t_server *server UNUSED, t_client *client,
		     char *arg UNUSED)
{
  t_string	string;
  int		i;

  string_init(&string);
  if (string_append(&string, "{", ALLOC_SIZE) == NULL)
    return (-1);
  for (i = 0; i < ITEM_PROB; ++i)
    if (list_player_inventory(&string, client->player, i) == -1)
      return (-1);
  if (string_append(&string, "}\n", ALLOC_SIZE) == NULL)
    return (-1);
  queue_push(&client->queue, string.content);
  free(string.content);
  return (0);
}
