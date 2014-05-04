/*
** util.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 17:02:27 2014 guillaume fillon
** Last update Sun May  4 17:05:04 2014 guillaume fillon
*/

#include <err.h>
#include <errno.h>

#include "server.h"

long		stoi(char *str)
{
  char		*endp;
  long		nb;

  errno = 0;
  endp = NULL;
  nb = strtol(str, &endp, 10);
  if ((endp != str && *endp != '\0') || endp == str || errno == ERANGE)
    warn("%s", str);
  return (nb);
}
