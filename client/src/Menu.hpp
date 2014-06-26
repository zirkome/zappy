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
# include "AWidget.hpp"

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
  void	launchGame();
  void	textInput(std::string &buf, unsigned int maxlen);
  void	setDone(bool done = true);
private:
  bool	textFillBuf(std::string &buf, unsigned int maxlen, Keycode key);
  void	handleClock(int &frame, double &time, double fps);
  void	freePanel(std::vector<AWidget *> &panel);

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  int			_frames;
  bool			_done;
  Cube			_cube;
  Input			*_input;
  Settings		*_set;
  GameEngine		_gameEngine;
  gdl::Clock		*_clock;
  std::vector<AWidget *> _mainPanel;
};

#endif /* _MENU_HPP_ */
