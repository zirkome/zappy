/*
** strings_getter.c for string_getter in /home/sinet_l/Documents/project/zappy/libsocket/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jul  7 10:28:31 2014 luc sinet
** Last update Mon Jul  7 20:51:39 2014 luc sinet
*/

#include "strings.h"

int	string_size(t_string *string)
{
  return (string->content == NULL ? 0 : strlen(string->content));
}

int	string_alloc_size(t_string *string)
{
  return (string->size);
}

int	string_empty(t_string *string)
{
  return (string->content == NULL || string->content[0] == '\0');
}
