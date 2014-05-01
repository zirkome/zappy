/*
** create_inet_server_socket.c for libsocket in libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 19:12:37 2014 guillaume fillon
** Last update Thu May  1 15:57:44 2014 guillaume fillon
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

static int		check_result(struct addrinfo *result)
{
  int			sfd;
  struct addrinfo	*res;

  res = result;
  while (NULL != res)
    {
      if ((sfd = socket_inet2(res->ai_family, res->ai_socktype,
			      res->ai_protocol)) > 0)
	{
	  if (bind_inet2(sfd, res->ai_addr, res->ai_addrlen) < 0)
	    return (-1);
	  if (listen(sfd, LIBSOCKET_BACKLOG) == 0)
	    break;
	  close(sfd);
	  res = res->ai_next;
	  continue;
	}
      res = res->ai_next;
    }
  if (res == NULL)
    {
      close(sfd);
      sfd = -1;
    }
  return (sfd);
}

int			create_inet_server_socket(const char* host,
						  const char* service)
{
  int			sfd;
  int			ret;
  struct addrinfo	hint;
  struct addrinfo	*result;

  memset(&hint, 0, sizeof(hint));
  hint.ai_family = AF_UNSPEC;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_flags = AI_PASSIVE;
  if ((ret = getaddrinfo(host, service, &hint, &result)) != 0)
    {
      warn("getaddrinfo: %s", gai_strerror(ret));
      return (-1);
    }
  sfd = check_result(result);
  freeaddrinfo(result);
  return (sfd);
}
