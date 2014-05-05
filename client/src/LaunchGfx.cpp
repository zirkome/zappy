//
// launchGfx.cpp for  in /home/fritsc_h/zappy/client
// 
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
// 
// Started on  Sat May  3 16:21:13 2014 Harold Fritsch
// Last update Sat May  3 16:22:59 2014 Harold Fritsch
//

#include <iostream>
#include "GameEngine.hpp"
#include "Exception.hpp"


int	launchGfx()
{
  try
    {
      GameEngine eng;

      if (!eng.initialize())
	return (1);
      while (eng.update())
	eng.draw();
      return (0);
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
