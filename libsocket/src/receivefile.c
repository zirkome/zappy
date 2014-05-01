/*
** receivefile.c for ftp in /home/kokaz/projects/tek2/unix/PSU_2013_myftp/libsocket/src
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Apr 13 18:29:43 2014 guillaume fillon
** Last update Sun Apr 13 23:19:49 2014 guillaume fillon
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

ssize_t		receivefile(int out_fd, int in_fd)
{
  size_t	total;
  ssize_t	r_ret;
  ssize_t	w_ret;
  char		buf[16 * BUFSIZ];

  total = 0;
  while ((r_ret = read(in_fd, buf, sizeof(buf))) > 0)
    {
      while ((w_ret = write(out_fd, buf, r_ret)) > 0)
	{
	  r_ret -= w_ret;
	  total += w_ret;
	}
      if (w_ret < 0)
	break;
    }
  return (total);
}
