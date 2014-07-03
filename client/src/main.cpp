#include <iostream>
#include <libsocket.h>
#include "Menu.hpp"

void	usage(const char *name)
{
  std::cerr << "Usage: " << name << " ip [port = 6000]" << std::endl;
}

int	main()
{
  try
    {
      Menu		menu;

      menu.initialize();
      while (menu.update() != false)
	menu.draw();
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
