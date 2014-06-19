/*
** pars.c for pars in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:46:12 2014 luc sinet
** Last update Thu Jun 19 21:25:10 2014 luc sinet
*/

#include "server.h"

static	t_command	g_command[] =
{
  {"avance", false, none,  NULL},
  {"droite", false, none, NULL},
  {"gauche", false, none, NULL},
  {"voir", false, none, NULL},
  {"inventaire", false, none, NULL},
  {"prend", true, string, NULL},
  {"pose", true, string, NULL},
  {"expulse", false, none, NULL},
  {"broadcast", true, string, NULL},
  {"incantation", false, none, NULL},
  {"fork", false, none, NULL},
  {"connect_nbr", false, none, NULL},
  {"msz", false, none, NULL},
  {"bct", true, string, NULL},
  {"mct", false, none, NULL},
  {"tna", false, none, NULL},
  {"ppo", true, number, NULL},
  {"plv", true, number, NULL},
  {"pin", true, number, NULL},
  {"sgt", false, none, NULL},
  {"sst", true, number, NULL},
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

int	parse_input(char *line, char *command, char *arg)
{
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
  char	command[CMDLEN];
  char	arg[ARGLEN];
  int	idx;

  if ((idx = parse_input(input, command, arg)) == -1)
    return (-1);
  write(1, command, strlen(command));
  write(1, " ", 1);
  write(1, arg, strlen(arg));
  write(1, "\n", 1);
  return (0);
}
