#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <unistd.h>
# include <OpenGL.hh>
# include <Game.hh>
# include <SdlContext.hh>
# include <BasicShader.hh>
# include <Clock.hh>
# include "GNetwork.hpp"
# include "Camera.hpp"
# include "Cube.hpp"
# include "Map.hpp"
# include "Input.hpp"

typedef struct	s_display
{
  Map			   map;
  std::vector<std::string> team;
  std::string		   win;
  int			   time;
  bool			   loading;
}		t_display;

class GameEngine : public gdl::Game
{
public:
  GameEngine(GNetwork *);
  virtual ~GameEngine();

  virtual bool update();
  virtual bool initialize();
  virtual void draw();

private:
  gdl::SdlContext		_win;
  Input				_input;
  gdl::Clock			_clock;
  gdl::BasicShader	        _shader;
  Cube				_ground;
  // Square			_loading;
  std::vector<IObject *>	_resources;
  Camera			_cam;
  GNetwork			*_socket;
  t_display			 _display;
};

#endif /* _GAMEENGINE_HPP_ */
