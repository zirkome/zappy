/*
** read_socket_inet.c for ftp in /home/kokaz/projects/tek2/unix/PSU_2013_myftp/libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:28:56 2014 guillaume fillon
** Last update Sun Apr 13 18:29:01 2014 guillaume fillon
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

ssize_t		read_socket_inet(int fd, char *buf, size_t size)
{
  ssize_t	ret;

  if ((ret = read(fd, buf, size - 1)) < 0)
    {
      fprintf(stderr, "Connection closed by foreign host\n");
      return ((ssize_t) -1);
    }
  buf[ret] = 0;
  write(1, buf, ret);
  return (ret);
}
