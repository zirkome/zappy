/*
** error.c for error in /home/sinet_l/Documents/project/irc/src/shared
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Apr 14 10:22:50 2014 luc sinet
** Last update Thu May 15 11:42:44 2014 Harold Fritsch
*/

#include <stdio.h>

int	ierror(const char *s, int ret)
{
  fprintf(stderr, "%s", s);
  return (ret);
}

void	*pterror(const char *s, void *ret)
{
  fprintf(stderr, "%s", s);
  return (ret);
}

int	iperror(const char *func, int ret)
{
  perror(func);
  return (ret);
}

void	*ptperror(const char *func, void *ret)
{
  perror(func);
  return (ret);
}
