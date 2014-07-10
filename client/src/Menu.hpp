#ifndef _MENU_HPP_
# define _MENU_HPP_

# include <Game.hh>
# include <SdlContext.hh>
# include <vector>
# include <algorithm>
# include <Clock.hh>
# include "Input.hpp"
# include "GameEngine.hpp"
# include "Settings.hpp"
# include "Text.hpp"
# include "GNetwork.hpp"
# include "AWidget.hpp"
# include "Sound.hpp"

# define MAPS_PATH "./Save/Maps/"
# define GAMES_PATH "./Save/Games/"

class Menu
{
public:
  Menu();
  virtual ~Menu();

  bool	initialize();
  bool	update();
  void	draw();
  void	launch();
  bool	launchGame();
  void	textInput(std::string &buf, unsigned int maxlen);
  void	setDone(bool done = true);
  bool	getInfo(std::string &ip, std::string &port);

private:
  bool	textFillBuf(std::string &buf, unsigned int maxlen, Keycode key);
  void	handleClock(int &frame, double &time, double fps);
  void	freePanel(std::vector<AWidget *> &panel);

  gdl::SdlContext	_win;
  GNetwork		_gNetwork;
  Settings		_set;
  gdl::Clock		_clock;
  Input			_input;
  GameEngine		*_gameEngine;
  gdl::BasicShader	_textShader;
  int			_frames;
  bool			_done;
  std::vector<AWidget *> _mainPanel;
  Sound			_sound;
};

#endif /* _MENU_HPP_ */
