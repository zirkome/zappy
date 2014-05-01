/*
** accept_inet.c for ftp in /home/kokaz/projects/tek2/unix/PSU_2013_myftp/libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:28:36 2014 guillaume fillon
** Last update Sun Apr 13 18:28:45 2014 guillaume fillon
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

int		accept_inet(int fd, struct sockaddr_in *addr)
{
  socklen_t	socklen;
  int		client;

  socklen = (socklen_t) sizeof(*addr);
  if ((client = accept(fd, (struct sockaddr *) addr, &socklen)) == -1)
    {
      warn("accept failed");
      if (close(fd) == -1)
	{
	  warn("close failed");
	  return (-1);
	}
      return (-1);
    }
  return (client);
}
