/*
** strings.c for strings in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sat Jun 21 13:39:46 2014 luc sinet
** Last update Sun Jun 22 20:18:45 2014 luc sinet
*/

#include "server.h"

char		*string_append(char *str, char *app, int *str_size)
{
  int		len;
  t_bool	init;;

  init = (str == NULL);
  len = (init ? 0 : strlen(str)) + strlen(app) + 1;
  if (len > *str_size)
    {
      *str_size = ALIGN(len, ALLOC_SIZE);
      if ((str = realloc(str, *str_size)) == NULL)
	return (NULL);
    }
  return (init ? strcpy(str, app) : strcat(str, app));
}
