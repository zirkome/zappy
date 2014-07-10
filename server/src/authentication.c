/*
** authentication.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 26 15:24:27 2014 guillaume fillon
** Last update Wed Jul  9 23:03:00 2014 guillaume fillon
*/

#include "server.h"
#include "gui.h"

static t_bool	get_command(char *line, char *command)
{
  int		i;

  i = 0;
  while (line[i] && line[i] != ' ' && i < CMDLEN)
    {
      command[i] = line[i];
      ++i;
    }
  if (i >= CMDLEN)
    return (false);
  command[i] = '\0';
  return (true);
}

void		clone_if_egg(t_server *server, t_list *list,
			     t_client *cl, t_team *team)
{
  t_node	*it;
  t_client	*client;
  t_job		*foodjob;
  t_gui_arg	garg;

  for (it = *list; it != NULL; it = it->next)
    {
      client = (t_client *)it->value;
      if (client->type == EGG && client->player->teamptr == team)
	{
	  garg.id = client->player->id;
	  gui_events_handling(server, client, &garg, &gui_egg_connect);
	  foodjob = cl->player->foodjob;
	  *(cl->player) = *(client->player);
	  cl->player->foodjob = foodjob;
	  disconnect_user(NULL, client);
	  break ;
	}
    }
}

int		check_remaining_slots(t_server *server, t_list *list,
				      t_client *cl, char *command)
{
  int		i;
  t_world	*w;

  w = &server->world;
  for (i = 0; i < w->nb_teams; ++i)
    if (strcmp(command, w->teams[i].name) == 0 && w->teams[i].slots > 0)
      {
	clone_if_egg(server, list, cl, &w->teams[i]);
	cl->player->teamptr = &w->teams[i];
	cl->type = IA;
	--w->teams[i].slots;
	add_to_world(w, PLAYER, cl->player->x, cl->player->y);
	queue_push_message(&cl->queue, "%d\n", w->teams[i].slots);
	queue_push_message(&cl->queue, "%d %d\n", w->width, w->height);
	gui_events_handling(server, cl, NULL, &gui_player_connect);
	return (0);
      }
  return (-2);
}

int	authenticate_user(t_server *server, t_client *cl, char *input)
{
  char	command[CMDLEN];

  get_command(input, command);
  if (strcmp(command, "GRAPHIC") == 0)
    {
      cl->type = GRAPHIC;
      gui_welcome(server, cl);
      return (0);
    }
  else
    return (check_remaining_slots(server, &server->cl, cl, command));
  return (-2);
}
