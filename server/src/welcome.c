/*
** welcome.c for welcome in /home/sinet_l/Documents/project/PSU_2013_myftp/src/serveur
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Apr  8 13:05:39 2014 luc sinet
** Last update Sat May  3 15:58:57 2014 luc sinet
*/

#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/netdevice.h>
#include "server.h"

int		get_time(char **date)
{
  time_t	ltime;

  if (time(&ltime) == (time_t)-1 || ((*date) = ctime(&ltime)) == NULL)
    return (iperror("get_time", -1));
  return (0);
}

int			print_ip(struct ifreq *ifreq, int interfaces)
{
  struct sockaddr_in	*address;
  char			ip[INET_ADDRSTRLEN];
  int			i;

  i = 0;
  while (i < interfaces)
    {
      address = (struct sockaddr_in *)&ifreq[i].ifr_addr;
      memset(ip, 0, sizeof(ip));
      if (!inet_ntop(AF_INET, &address->sin_addr, ip, INET_ADDRSTRLEN))
	return (-1);
      printf("- %s\n", ip);
      ++i;
    }
  return (0);
}

int			list_ip()
{
  struct ifconf		ifconf;
  struct ifreq		ifreq[20];
  int			sock;
  int			interfaces;
  int			ret;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return (iperror("list_ip: socket", -1));
  ifconf.ifc_buf = (char *)ifreq;
  ifconf.ifc_len = sizeof(ifreq);
  if (ioctl(sock, SIOCGIFCONF, &ifconf) == -1)
    {
      close(sock);
      return (iperror("list_ip: ioctl", -1));
    }
  interfaces = ifconf.ifc_len / sizeof(struct ifreq);
  interfaces = (interfaces > 20) ? 20 : interfaces;
  ret = print_ip(ifreq, interfaces);
  close(sock);
  return (ret);
}

void	welcome_server(int port)
{
  char	*date;

  if (get_time(&date) == -1)
    return ;
  printf("Welcome !\n%s\n"
	 "Port used: %d\n"
	 "Server's ip:\n", date, port);
  list_ip();
  fflush(stdout);
}
