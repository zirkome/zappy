#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <unistd.h>
# include <Game.hh>
# include <SdlContext.hh>
# include <Input.hh>

class GameEngine : public gdl::Game
{
public:
  GameEngine();
  virtual ~GameEngine();

  virtual bool update();
  virtual bool initialize();
  virtual void draw();

private:
  gdl::SdlContext _win;
  gdl::Input	  _input;
};

#endif /* _GAMEENGINE_HPP_ */
