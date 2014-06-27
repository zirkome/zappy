/*
** strings.c for strings in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 21 13:39:46 2014 luc sinet
** Last update Fri Jun 27 19:35:36 2014 luc sinet
*/

#include "server.h"

void		string_init(t_string *string)
{
  string->content = NULL;
  string->size = 0;
}

char		*string_append(t_string *string, char *app, int align_size)
{
  int		len;
  t_bool	init;

  init = (string->content == NULL);
  len = (init ? 0 : strlen(string->content)) + strlen(app) + 1;
  if (len > string->size)
    {
      string->size = ALIGN(len, align_size);
      if ((string->content = realloc(string->content, string->size)) == NULL)
	return (ptperror("string_append: realloc", NULL));
    }
  return (init ? strcpy(string->content, app) : strcat(string->content, app));
}

int	string_erase(t_string *string, int type)
{
  char	*content;
  int	i;

  content = string->content;
  if (content == NULL)
    return (-1);
  for (i = 0; content[i] && content[i] != type; ++i);
  if (!content[i])
    return (-1);
  while (content[i + 1])
    {
      content[i] = content[i + 1];
      ++i;
    }
  content[i] = '\0';
  return (0);
}
