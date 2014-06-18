#include <iostream>
#include "libsocket.h"

void	usage(const char *name)
{
  std::cerr << "Usage: " << name << " ip [port = 6000]" << std::endl;
}

int		main(int ac, char **av)
{
  std::string ip;
  std::string port;
  int fdSocket;

  if (ac < 2)
    {
      usage(av[0]);
      return (1);
    }
  ip = av[1];
  if (ac > 2)
    port = av[2];
  else
    port = "6000";

  if ((fdSocket = create_inet_stream_socket(ip.c_str(), port.c_str(), 0)) < 0)
    return (1);
  write_socket_inet(fdSocket, "TOTO", 4);
  close(fdSocket);
  return (0);
}
