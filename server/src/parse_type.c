#include "server.h"

t_bool	is_number(char c)
{
  return (c >= '0' && c <= '9');
}

t_type	get_type(char *line)
{
  if (!line[0])
    return (none);
  for (int i = 0; line[i]; ++i)
    if (!is_number(line[i]))
      return (string);
  return (number);
}

t_bool	check_argument_type(char *arg, t_command *cmds, int idx)
{
  if (idx == PPO || idx == PLV || idx == PIN)
    {
      if (arg[0] != '#')
	return (false);
      ++arg;
    }
  return (get_type(arg) == cmds[idx].type);
}
