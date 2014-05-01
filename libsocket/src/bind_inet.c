/*
** bind_inet.c for ftp in /home/kokaz/projects/tek2/unix/PSU_2013_myftp/libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:28:10 2014 guillaume fillon
** Last update Sun Apr 13 23:05:54 2014 guillaume fillon
*/

#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "inet_socket.h"

int	bind_inet2(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
  if (bind(fd, addr, addrlen) == -1)
    {
      warn("bind failed");
      if (close(fd) == -1)
	{
	  warn("close failed");
	  return (-1);
	}
      return (-1);
    }
  return (fd);
}

int			bind_inet(int fd, const char *addr, in_port_t port)
{
  struct sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(addr);
  sin.sin_port = htons(port);
  if (bind(fd, (const struct sockaddr*) &sin, sizeof(sin)) == -1)
    {
      warn("bind failed");
      if (close(fd) == -1)
	{
	  warn("close failed");
	  return (-1);
	}
      return (-1);
    }
  return (fd);
}