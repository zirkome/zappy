/*
** write_socket_inet.c for ftp in /home/kokaz/projects/tek2/unix/PSU_2013_myftp/libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:29:11 2014 guillaume fillon
** Last update Sun Apr 13 18:29:24 2014 guillaume fillon
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

ssize_t		write_socket_inet(int fd, char *buf, size_t size)
{
  ssize_t	ret;

  if ((ret = write(fd, buf, size)) < 0)
    {
      fprintf(stderr, "Connection closed by foreign host\n");
      return ((ssize_t) -1);
    }
  return (ret);
}
