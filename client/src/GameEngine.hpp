#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <unistd.h>
# include <vector>
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
# include "Settings.hpp"
# include "Light.hpp"
# include "Console.hpp"

# define CHANGETIME 1

# define ASSETS_DIR "./assets/"

# define LOADING_TEXTURE ASSETS_DIR"loading.tga"
# define GROUND_TEXTURE ASSETS_DIR"ground.tga"

# define FOOD_MODEL ASSETS_DIR"hamburger.fbx"
# define LINEMATE_MODEL ASSETS_DIR"knife.fbx"
# define DERAUMERE_MODEL ASSETS_DIR"pistol.fbx"
# define SIBUR_MODEL ASSETS_DIR"mp5.fbx"
# define MENDIANE_MODEL ASSETS_DIR"ak47.fbx"
# define PHIRAS_MODEL ASSETS_DIR"svd.fbx"
# define THYSTAME_MODEL ASSETS_DIR"rpg.fbx"

# define PLAYER_MODEL ASSETS_DIR"CJ.fbx"
# define EGG_MODEL ASSETS_DIR"CJ.fbx"


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
  GameEngine(GNetwork *_gNetwork, gdl::SdlContext *win, Settings *set, Input *input);
  virtual ~GameEngine();

  virtual bool update();
  virtual bool initialize();
  virtual void draw();

private:
  void displayItem(const char flag, int x, int y);

  GNetwork			*_socket;
  gdl::SdlContext		*_win;
  Settings			*_set;
  Input				*_input;
  gdl::Clock			_clock;
  gdl::BasicShader	        _shader;
  Console			_console;
  gdl::BasicShader	        _textShader;
  Cube				_ground;
  Square			_loading;
  std::vector<Model *>		_resources;
  Model		       		_player;
  Model			       	_egg;
  Camera			_cam;
  t_display			_display;
  std::vector<Light *>		_lights;
};

#endif /* _GAMEENGINE_HPP_ */
