/*
** util.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 17:02:27 2014 guillaume fillon
** Last update Wed Jul  9 14:09:08 2014 guillaume fillon
*/

#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include "server.h"

struct epoll_event	create_event(struct epoll_event	*ev, int fd, int flags)
{
  ev.events = flags;
  ev.data.ptr = NULL;
  ev.data.fd = fd;
  return (ev);
}

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

void		queue_push_message(t_queue **queue, const char *format, ...)
{
  char		*str;
  va_list	ap;

  va_start(ap, format);
  str = vcnprintf(BUFSIZ, format, ap);
  va_end(ap);
  queue_push(queue, str);
  free(str);
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
