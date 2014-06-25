#ifndef _MENU_HPP_
# define _MENU_HPP_

# include <Game.hh>
# include <SdlContext.hh>
# include <vector>
# include <algorithm>
# include "Settings.hpp"
# include "Input.hpp"
# include "GameEngine.hpp"
# include "Text.hpp"
# include "Sound.hpp"
# include "AWidget.hpp"
# include "Console.hpp"
# include "Intro.hpp"
# include "Chicken.hpp"

# define SCORE_PATH "./.scores"
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
  void	launchGame(const std::string &file, int load);
  void	textInput(std::string &buf, unsigned int maxlen);

private:
  bool	textFillBuf(std::string &buf, unsigned int maxlen, Keycode key);
  void	handleClock(int &frame, double &time, double fps);
  void	freePanel(AWidget *background, AWidget *title,
		  AWidget *back, std::vector<AWidget *> &panel);

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  bool			_done;
  bool			_multi;
  t_gameinfo		_gameInfo;
  GameEngine		_gameEngine;
  int			_frames;
  Cube			_cube;
  unsigned int		 _filePos;
  std::list<std::string> _filename;
  std::vector<AWidget *> _mainPanel;
  Player		 *_player1;
  Player		 *_player2;
};

#endif /* _MENU_HPP_ */
