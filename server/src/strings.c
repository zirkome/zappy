/*
** strings.c for strings in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 21 13:39:46 2014 luc sinet
** Last update Tue Jun 24 11:53:26 2014 luc sinet
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
