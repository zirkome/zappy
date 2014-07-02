/*
** pars.c for pars in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Fri May  2 22:46:12 2014 luc sinet
** Last update Wed Jul  2 22:29:00 2014 guillaume fillon
*/

#include "scheduler.h"
#include "server.h"

static	t_command	g_command[] =
{
  {"avance", false, none,  &pl_forward, 7},
  {"droite", false, none, &pl_right, 7},
  {"gauche", false, none, &pl_left, 7},
  {"voir", false, none, &pl_see, 7},
  {"inventaire", false, none, &pl_inventory, 7},
  {"prend", true, string, &pl_take, 7},
  {"pose", true, string, &pl_put, 7},
  {"expulse", false, none, &pl_expulse, 7},
  {"broadcast", true, string, &pl_broadcast, 7},
  {"incantation", false, none, &pl_incantation, 300},
  {"fork", false, none, &pl_lay_egg, 42},
  {"connect_nbr", false, none, &pl_connect_nbr, 0},
  {"msz", false, none, &gui_msz, 0},
  {"bct", true, string, &gui_bct, 0},
  {"mct", false, none, &gui_mct, 0},
  {"tna", false, none, &gui_tna, 0},
  {"ppo", true, number, &gui_ppo, 0},
  {"plv", true, number, &gui_plv, 0},
  {"pin", true, number, &gui_pin, 0},
  {"sgt", false, none, &gui_sgt, 0},
  {"sst", true, number, &gui_sst, 0},
  {NULL, false, none, NULL, 0}
};

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

static int	get_argument(char *line, char *arg, t_bool need_arg)
{
  int		i;
  int		j;

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

static int	parse_input(char *line, char *arg)
{
  char		command[CMDLEN];
  int		i;

  i = 0;
  if (get_command(line, command) == false)
    return (-1);
  while (g_command[i].name && strcmp(g_command[i].name, command) != 0)
    ++i;
  if (g_command[i].name == NULL ||
      get_argument(&line[strlen(command)], arg, g_command[i].arg) == false ||
      check_argument_type(arg, &g_command[i]) == false)
    return (-1);
  if (g_command[i].arg == true && i != BROADCAST)
    {
      if (check_argument_type(arg, &g_command[i]) == false)
	return (-1);
    }
  return (i);
}

int		process_input(t_server *server, t_client *cl, char *input)
{
  struct s_job	task;
  char		arg[ARGLEN];
  int		idx;

  if (cl->type == UNKNOWN)
    return (authenticate_user(server, cl, input));
  printf("Got input: %s\n", input);
  if ((idx = parse_input(input, arg)) == -1)
    return (-1);
  task.client = cl;
  task.at = g_command[idx].delay / server->world.delay;
  task.callback = g_command[idx].func;
  if ((task.arg = strdup(arg)) == NULL)
    return (iperror("process_input: strdup", -1));
  return (scheduler_add(&cl->player->jobs, &task));
}
