/*
** util.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 17:02:27 2014 guillaume fillon
** Last update Fri Jun 27 23:58:50 2014 guillaume fillon
*/

#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include "server.h"

char	*vcnprintf(size_t size, const char *format, va_list ap)
{
  char	buf[BUFSIZ];

  if (size > BUFSIZ)
    return (NULL);
  if (vsnprintf(buf, size - 1, format, ap) < 0)
    return (NULL);
  return (strdup(buf));
}

char		*cnprintf(size_t size, const char *format, ...)
{
  char		*str;
  va_list	ap;

  va_start(ap, format);
  str = vcnprintf(size, format, ap);
  va_end(ap);
  return (str);
}

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
