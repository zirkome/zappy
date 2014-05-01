/*
** socket_inet.c for ftp in /home/kokaz/projects/tek2/unix/PSU_2013_myftp/libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:27:20 2014 guillaume fillon
** Last update Fri Apr 18 14:44:08 2014 guillaume fillon
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

int			socket_inet(int type, const char const *proto)
{
  int			yes;
  int			fd;
  struct protoent	*pe;

  yes = 1;
  if (proto == NULL)
    pe = getprotobyname("TCP");
  else
    pe = getprotobyname(proto);
  if (pe == NULL)
    return (-1);
  fd = socket(AF_INET, type, pe->p_proto);
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    warn("setsockopt failed");
  return (fd);
}

int	socket_inet2(int domain, int type, int protocol)
{
  int	yes;
  int	fd;

  yes = 1;
  fd = socket(domain, type, protocol);
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    warn("setsockopt failed");
  return (fd);
}
