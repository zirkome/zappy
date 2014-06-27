/*
** authentication.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Jun 26 15:24:27 2014 guillaume fillon
** Last update Fri Jun 27 11:30:18 2014 guillaume fillon
*/

#include "server.h"

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

int		authenticate_user(t_server *server, t_client *cl, char *input)
{
  char		*msg;
  char		command[CMDLEN];
  int		i;
  t_world	w;

  get_command(input, command);
  if (strcmp(command, "GRAPHIC") == 0)
    {
      cl->type = GRAPHIC;
      gui_welcome(server, cl);
      return (0);
    }
  else
    {
      w = server->world;
      for (i = 0; i < w.nb_teams; ++i)
	if (strcmp(command, w.teams[i].name) == 0 && w.teams[i].slots > 0)
	  {
	    cl->player->teamptr = &w.teams[i];
	    cl->type = IA;
	    --w.teams[i].slots;
	    msg = cnprintf(10, "%d\n", w.teams[i].slots);
	    queue_push(&cl->queue, msg);
	    free(msg);
	    msg = cnprintf(10, "%d %d\n", w.width, w.height);
	    queue_push(&cl->queue, msg);
	    free(msg);
	    return (0);
	  }
    }
  return (-2);
}
