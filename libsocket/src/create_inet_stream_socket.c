/*
** create_inet_stream_socket.c for libsocket in libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:55:41 2014 guillaume fillon
** Last update Thu May  1 16:25:03 2014 luc sinet
*/

#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include "inet_socket.h"

static int		check_result(struct addrinfo *result, int flags)
{
  int			sfd;
  struct addrinfo	*res;

  res = result;
  while (NULL != res)
    {
      if ((sfd = socket(res->ai_family, res->ai_socktype | flags,
			res->ai_protocol)) > 0)
	if (connect(sfd, res->ai_addr, res->ai_addrlen) == 0)
	  break;
      res = res->ai_next;
    }
  if (res == NULL)
    {
      close(sfd);
      sfd = -1;
    }
  return (sfd);
}

int			create_inet_stream_socket(const char* host,
						  const char* service,
						  int flags)
{
  int			sfd;
  int			ret;
  struct addrinfo	hint;
  struct addrinfo	*result;

  if (host == NULL || service == NULL)
    return (-1);
  memset(&hint, 0, sizeof(hint));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  if ((ret = getaddrinfo(host, service, &hint, &result)) != 0)
    {
      warn("getaddrinfo: %s", gai_strerror(ret));
      return (-1);
    }
  sfd = check_result(result, flags);
  freeaddrinfo(result);
  return (sfd);
}
