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
# include "Square.hpp"
# include "Model.hpp"

# define ASSETS_DIR "./assets/"

# define LOADING_TEXTURE ASSETS_DIR"loading.tga"
# define GROUND_TEXTURE ASSETS_DIR"ground.tga"

# define FOOD_MODEL ASSETS_DIR""
# define LINEMATE_MODEL ASSETS_DIR""
# define DERAUMERE_MODEL ASSETS_DIR""
# define SIBUR_MODEL ASSETS_DIR""
# define MENDIANE_MODEL ASSETS_DIR""
# define PHIRAS_MODEL ASSETS_DIR""
# define THYSTAME_MODEL ASSETS_DIR""

# define PLAYER_MODEL ASSETS_DIR""
# define EGG_MODEL ASSETS_DIR""


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
  void displayItem(const char flag, int x, int y);

  gdl::SdlContext		_win;
  Input				_input;
  gdl::Clock			_clock;
  gdl::BasicShader	        _shader;
  gdl::BasicShader	        _textShader;
  Cube				_ground;
  Square			_loading;
  std::vector<Model *>		_resources;
  Model		       		_player;
  Model			       	_egg;
  Camera			_cam;
  GNetwork			*_socket;
  t_display			 _display;
};

#endif /* _GAMEENGINE_HPP_ */
