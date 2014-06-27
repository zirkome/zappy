/*
** player_inventory.c for inventory in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri Jun 27 21:42:58 2014 luc sinet
** Last update Fri Jun 27 22:52:56 2014 luc sinet
*/

#include "server.h"

int	add_to_inventory(t_player *player, int type, int amount)
{
  if (type <= 0 || type >= PLAYER)
    return (-1);
  player->inventory[type] += amount;
  return (0);
}

int	remove_from_inventory(t_player *player, int type, int amount)
{
  if (type <= 0 || type >= NB_ELEM || player->inventory[type] == 0)
    return (-1);
  player->inventory[type] -= amount;
  return (0);
}

int	pl_inventory(t_server *server UNUSED, t_client *client UNUSED,
		     char *arg UNUSED)
{
  return (0);
}
