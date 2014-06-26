#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <unistd.h>
# include <OpenGL.hh>
# include <Game.hh>
# include <SdlContext.hh>
# include <BasicShader.hh>
# include <Input.hh>
# include <Clock.hh>
# include "GNetwork.hpp"
# include "Camera.hpp"
# include "Cube.hpp"
# include "Map.hpp"

class GameEngine : public gdl::Game
{
public:
  GameEngine(GNetwork *);
  virtual ~GameEngine();

  virtual bool update();
  virtual bool initialize();
  virtual void draw();

private:
  gdl::SdlContext  _win;
  gdl::Input	   _input;
  gdl::Clock	   _clock;
  gdl::BasicShader _shader;
  Cube             _cube;
  Camera	   _cam;
  bool		   _isPlaying;
  GNetwork	   *_socket;
  Map		   _map;
};

#endif /* _GAMEENGINE_HPP_ */
