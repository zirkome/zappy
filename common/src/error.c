/*
** error.c for error in /home/sinet_l/Documents/project/irc/src/shared
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Apr 14 10:22:50 2014 luc sinet
** Last update Mon Jun 16 10:57:35 2014 guillaume fillon
*/

#include <stdio.h>
#include <err.h>

int	ierror(const char *s, int ret)
{
  fprintf(stderr, "%s\n", s);
  return (ret);
}

void	*pterror(const char *s, void *ret)
{
  fprintf(stderr, "%s\n", s);
  return (ret);
}

int	iperror(const char *func, int ret)
{
  warn("%s", func);
  return (ret);
}

void	*ptperror(const char *func, void *ret)
{
  warn("%s", func);
  return (ret);
}
