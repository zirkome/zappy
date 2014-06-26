#include <iostream>
#include <libsocket.h>
#include "GameEngine.hpp"

void	usage(const char *name)
{
  std::cerr << "Usage: " << name << " ip [port = 6000]" << std::endl;
}

int	main(int ac, char **av)
{
  try
    {
      std::string	ip, port;
      GNetwork	serv;
      GameEngine	gameEngine(&serv);

      if (ac < 2)
	{
	  usage(av[0]);
	  return (1);
	}
      ip = av[1];
      if (ac > 2)
	port = av[2];
      else
	port = std::string("6000");
      if (!serv.open(ip.c_str(), port.c_str()))
	return (1);
      gameEngine.initialize();
      while (gameEngine.update())
	gameEngine.draw();
      serv.close();
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  catch (std::bad_alloc& ba)
    {
      std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
    }
  return (0);
}
