#include "server.h"

t_bool	is_number(char c)
{
  return (c >= '0' && c <= '9');
}

t_arg_type	get_type(char *line)
{
  int		i;

  if (!line[0])
    return (none);
  for (i = 0; line[i]; ++i)
    if (!is_number(line[i]))
      return (string);
  return (number);
}

t_bool	check_argument_type(char *arg, t_command *cmd)
{
  return (get_type(arg) == cmd->type);
}
