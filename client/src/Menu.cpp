#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include "Menu.hpp"
#include "NavigationWidget.hpp"
#include "ImageWidget.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
  AWidget	*background;
  AWidget	*title;
  AWidget	*quit;

  background = *_newGamePanelSolo.begin();
  title = *(_newGamePanelSolo.begin() + 1);
  quit = *(_newGamePanelSolo.begin() + 2);
  delete background;
  delete title;
  delete back;
  freePanel(background, title, back, _mainPanel);
}

void	Menu::freePanel(AWidget *background, AWidget *title,
			AWidget *quit, std::vector<AWidget *> &panel)
{
  std::vector<AWidget *>::iterator	it;
  std::vector<AWidget *>::iterator	end;

  for (it = panel.begin(), end = panel.end(); it != end; ++it)
    {
      if (*it != quit && *it != title && *it != background)
	delete (*it);
    }
}

bool  Menu::initialize()
{
  int x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);

  if (!_win.start(x, y, "Zappy", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL))
    throw(Exception("Cannot open window"));
  if (!_gameEngine.initialize())
    return (false);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER) ||
      !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER) ||
      !_textShader.build())
    return (false);

  ImageWidget	*background = new ImageWidget(0, 0, y, x,
					      "./assets/background.tga");
  ImageWidget	*title = new ImageWidget(x / 8, y / 1.43f, y / 4.8f, x / 1.3f,
					 "./assets/BomberCraft.tga");
  _mainPanel.push_back(background);
  _mainPanel.push_back(title);
  _mainPanel.push_back(new QuitWidget(x / 4, y / 18, y / 11.25f, x / 2, "./assets/button/quit.tga"));
  // add 2 inputWidget

  return (true);
}

bool		Menu::update()
{
  double	time;
  double	fps = (1000 / _gameInfo.set->getVar(FPS));
  int		y = _gameInfo.set->getVar(W_HEIGHT);
  t_window	win;
  t_mouse	mouse;

  _gameEngine.resetAlreadyPlayed();
  _gameInfo.input->getInput(*(_gameInfo.set));
  (*(_gameInfo.input))[mouse];
  (*_gameInfo.input)[win];
  if (mouse.event == BUTTONUP)
    for (std::vector<AWidget *>::iterator it = _mainPanel.begin(),
	   endit = _mainPanel.end(); it != endit ; ++it)
      if ((*it)->isClicked(mouse.x, y - mouse.y))
	{
	  (*it)->onClick(_gameInfo, (*this));
	  break;
	}
  _win.updateClock(*(_gameInfo.clock));
  if (_gameInfo.input->isPressed(SDLK_ESCAPE) || win.event == WIN_QUIT)
    return (false);
  _frames++;
  if ((time = _gameInfo.clock->getElapsed()) < fps)
    {
      _frames = 0;
      usleep((fps - time) * 1000);
    }
  return (true);
}

void	Menu::draw()
{
  float x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, x, y);
  glDisable(GL_DEPTH_TEST);
  _textShader.bind();
  _textShader.setUniform("projection", glm::ortho(0.0f, x, 0.0f, y, -1.0f, 1.0f));
  _textShader.setUniform("view", glm::mat4(1));
  _textShader.setUniform("winX", x);
  _textShader.setUniform("winY", y);
  for (std::vector<AWidget *>::iterator it = _mainPanel.begin(),
	 endit = _mainPanel.end(); it != endit ; ++it)
    {
      (*it)->onDisplay(_filename, _filePos);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      (*it)->draw(_textShader, *_gameInfo.clock);
    }
  glEnable(GL_DEPTH_TEST);
  _win.flush();
}

void	Menu::handleClock(int &frame, double &time, double fps)
{
  time = _gameInfo.clock->getElapsed();
  if (time < fps)
    usleep((fps - time) * 1000);
  frame = (frame >= 100) ? 100 : frame + 1;
  _win.updateClock(*_gameInfo.clock);
}

bool	Menu::textFillBuf(std::string &buf, unsigned int maxlen, Keycode key)
{
  if (key == '\r' || key == SDLK_KP_ENTER || key == 27)
    {
      buf.erase(buf.end() - 1);
      return (false);
    }
  else if (key > 0 && key < 128)
    {
      if (key == '\b' && buf.length() > 1)
	{
	  buf = buf.substr(0, buf.length() - 2);
	  buf.push_back('|');
	}
      else if (buf.length() < maxlen && key >= ' ' && key <= '~')
	{
	  buf.at(buf.length() - 1) = static_cast<char>(key);
	  buf.push_back('|');
	}
    }
  return (true);
}

void	Menu::textInput(std::string &buf, unsigned int maxlen)
{
  double	fps = 1000.0 / 25.0;
  double	time = 0;
  int		frame = -1;
  Keycode	key = 0;
  Keycode	save = -1;
  Input		*input = _gameInfo.input;

  buf.clear();
  buf.push_back('|');
  while (key != 27)
    {
      input->getInput(*(_gameInfo.set));
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      l_Keycit beg = input->getPressedBeg();
      l_Keycit end = input->getPressedEnd();
      if (beg != end && *beg == SDLK_LSHIFT)
	++beg;
      if (beg != end)
	{
	  key = *beg;
	  if (key >= SDLK_KP_1 && key <= SDLK_KP_0)
	    key = '0' + (key == SDLK_KP_0 ? (key - 10) : key) - SDLK_KP_1 + 1;
	  else if (key == SDLK_KP_PERIOD)
	    key = '.';
	  if (save == key)
	    {
	      if (((key < 128 && key != '\b') && frame < 8) ||
		  (key == '\b' && frame < 2) ||
		  ((key == '\r' || key == SDLK_KP_ENTER) && frame < 15))
		{
		  handleClock(frame, time, fps);
		  continue;
		}
	      else
		frame = 0;
	    }
	  else
	    frame = 0;
	  save = key;
	}
      for (; beg != end; ++beg)
	if (textFillBuf(buf, maxlen, key) == false)
	  return ;
      handleClock(frame, time, fps);
      draw();
    }
}

void	Menu::launchGame(const std::string &file, int load)
{
  Map map(*(_gameInfo.set));
  _gameInfo.map = &map;
  bool	done = true;

  _gameEngine.setShutdown(false);
  while ((done = _gameEngine.update()))
    _gameEngine.draw();
  _gameInfo.map = NULL;
}

void	Menu::launch()
{
  Intro intro;

  if (!initialize())
      return ;
  while (!_done)
    {
      if (update() == false)
	return ;
      draw();
    }
  _win.stop();
}

void	Menu::setDone(bool done)
{
  _done = done;
}
