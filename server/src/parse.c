/*
** pars.c for pars in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:46:12 2014 luc sinet
** Last update Thu Jun 26 16:40:23 2014 guillaume fillon
*/

#include "server.h"

static	t_command	g_command[] =
{
  {"avance", false, none,  &pl_forward},
  {"droite", false, none, &pl_right},
  {"gauche", false, none, &pl_left},
  {"voir", false, none, &pl_see},
  {"inventaire", false, none, &pl_inventory},
  {"prend", true, string, &pl_take},
  {"pose", true, string, &pl_put},
  {"expulse", false, none, &pl_expulse},
  {"broadcast", true, string, &pl_broadcast},
  {"incantation", false, none, &pl_incantation},
  {"fork", false, none, &pl_fork},
  {"connect_nbr", false, none, &pl_connect_nbr},
  {"msz", false, none, &gui_msz},
  {"bct", true, string, &gui_bct},
  {"mct", false, none, &gui_mct},
  {"tna", false, none, &gui_tna},
  {"ppo", true, number, &gui_ppo},
  {"plv", true, number, &gui_plv},
  {"pin", true, number, &gui_pin},
  {"sgt", false, none, &gui_sgt},
  {"sst", true, number, &gui_sst},
  {NULL, false, none, NULL}
};

t_bool	get_command(char *line, char *command)
{
  int	i;

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

int	get_argument(char *line, char *arg, t_bool need_arg)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (line[i] == ' ')
    ++i;
  if ((line[i] != '\0' && need_arg == false) ||
      (line[i] == '\0' && need_arg == true))
    return (false);
  while (line[i] && j < ARGLEN)
    arg[j++] = line[i++];
  if (j >= ARGLEN)
    return (false);
  arg[j] = '\0';
  return (true);
}

int	parse_input(char *line, char *arg)
{
  char	command[CMDLEN];
  int	i;

  i = 0;
  if (get_command(line, command) == false)
    return (-1);
  while (g_command[i].name && strcmp(g_command[i].name, command) != 0)
    ++i;
  if (g_command[i].name == NULL ||
      get_argument(&line[strlen(command)], arg, g_command[i].arg) == false ||
      check_argument_type(arg, g_command, i) == false)
    return (-1);
  if (g_command[i].arg == true && i != BROADCAST)
    {
      if (check_argument_type(arg, g_command, i) == false)
	return (-1);
    }
  return (i);
}

int	process_input(t_server *server, t_client *cl, char *input)
{
  char	arg[ARGLEN];
  int	idx;

  /* if (cl->type == UNKNOWN) */
  /*   return (authenticate_user(server, cl, input)); */
  printf("Got input: %s\n", input);
  if ((idx = parse_input(input, arg)) == -1)
    return (-1);
  if (idx < MSZ)
    g_command[idx].func(server, cl, arg);
  return (0);
}
