/*
** pars.c for pars in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:46:12 2014 luc sinet
** Last update Wed Jun 18 17:03:22 2014 luc sinet
*/

#include "server.h"

static	t_command	g_command[] =
{
  {"avance", false,  NULL},
  {"droite", false, NULL},
  {"gauche", false, NULL},
  {"voir", false, NULL},
  {"inventaire", false, NULL},
  {"prend", true, NULL},
  {"pose", true, NULL},
  {"expulse", false, NULL},
  {"broadcast", true, NULL},
  {"incantation", false, NULL},
  {"fork", false, NULL},
  {"connect_nbr", false, NULL},
  {"msz", false, NULL},
  {"bct", true, NULL},
  {"mct", false, NULL},
  {"ppo", true, NULL},
  {"plv", true, NULL},
  {"pin", true, NULL},
  {"sgt", false, NULL},
  {"sst", true, NULL},
  {NULL, false, NULL}
};

bool	get_command(char *line, char *command)
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

int	get_argument(char *line, char *arg, bool need_arg)
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
      get_argument(&line[strlen(command)], arg, g_command[i].arg) == false)
    return (-1);
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
