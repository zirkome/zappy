#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <Clock.hh>
#include "Menu.hpp"
#include "Settings.hpp"
#include "ImageWidget.hpp"
#include "QuitWidget.hpp"
#include "InputWidget.hpp"
#include "ConnectWidget.hpp"
#include "GameEngine.hpp"

Menu::Menu()
{
  _done = false;
  _gameEngine = NULL;
}

Menu::~Menu()
{
  freePanel(_mainPanel);
  _gNetwork.close();
}

void	Menu::freePanel(std::vector<AWidget *> &panel)
{
  std::vector<AWidget *>::iterator	it;
  std::vector<AWidget *>::iterator	end;

  for (it = panel.begin(), end = panel.end(); it != end; ++it)
    if (*it != NULL)
      delete (*it);
}

bool  Menu::initialize()
{
  int x = _set.getVar(W_WIDTH), y = _set.getVar(W_HEIGHT);

  if (!_win.start(x, y, "Zappy", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER) ||
      !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER) ||
      !_textShader.build())
    return (false);
  ImageWidget	*background = new ImageWidget(0, 0, y, x, "./assets/background.tga");
  ImageWidget	*title = new ImageWidget((1024 / 2) - ((340 * 1.25f) / 2), 400, 120 * 1.25f, 340 * 1.25f, "./assets/zappy.tga");
  _mainPanel.push_back(background);
  _mainPanel.push_back(title);
  _mainPanel.push_back(new InputWidget(x / 4, 9.5f * y / 18, y / 11.25f, x / 2, "./assets/input.tga", "IP :"));
  _mainPanel.push_back(new InputWidget(x / 4, 7.5f * y / 18, y / 11.25f, x / 2, "./assets/input.tga", "Port :"));
  _mainPanel.push_back(new ConnectWidget(x / 4, 5.5f * y / 18, y / 11.25f, x / 2, "./assets/button.tga"));
  _mainPanel.push_back(new QuitWidget(x / 4, y / 18, y / 11.25f, x / 2, "./assets/quit.tga"));
  return (true);
}

bool		Menu::update()
{
  double	time;
  double	fps = (1000 / _set.getVar(FPS));
  int		y = _set.getVar(W_HEIGHT);
  t_window	win;
  t_mouse	mouse;

  _input.getInput();
  _input[mouse];
  _input[win];
  if (mouse.event == BUTTONUP)
    for (std::vector<AWidget *>::iterator it = _mainPanel.begin(),
	   endit = _mainPanel.end(); it != endit ; ++it)
      if ((*it)->isClicked(mouse.x, y - mouse.y))
	{
	  (*it)->onClick((*this));
	  break;
	}
  _win.updateClock(_clock);
  if (_input.isPressed(SDLK_ESCAPE) || win.event == WIN_QUIT || _done == true)
    return (false);
  _frames++;
  if ((time = _clock.getElapsed()) < fps)
    {
      _frames = 0;
      usleep((fps - time) * 1000);
    }
  return (true);
}

void	Menu::draw()
{
  float x = _set.getVar(W_WIDTH), y = _set.getVar(W_HEIGHT);

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
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      (*it)->draw(_textShader, _clock);
    }
  glEnable(GL_DEPTH_TEST);
  _win.flush();
}

void	Menu::handleClock(int &frame, double &time, double fps)
{
  time = _clock.getElapsed();
  if (time < fps)
    usleep((fps - time) * 1000);
  frame = (frame >= 100) ? 100 : frame + 1;
  _win.updateClock(_clock);
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
  Input		*input = &_input;

  buf.clear();
  buf.push_back('|');
  while (key != 27)
    {
      _input.getInput();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      l_Keycit beg = _input.getPressedBeg();
      l_Keycit end = _input.getPressedEnd();
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

bool	Menu::launchGame()
{
  std::string ip = "FREE", port = "6000";

  if (getInfo(ip, port) == true)
    {
      _gameEngine = new GameEngine(&_gNetwork, &_win);
      if (!_gNetwork.open(ip.c_str(), port.c_str()))
	throw Exception("cannot connect to the server"); // replace exception by error
      _gameEngine->initialize();
      while (_gameEngine->update())
	_gameEngine->draw();
      return (true);
    }
  else
    return (false);
}

void	Menu::launch()
{
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

bool Menu::getInfo(std::string &ip, std::string &port)
{
  ip = dynamic_cast<InputWidget *>(_mainPanel[2])->getContent();
  port = dynamic_cast<InputWidget *>(_mainPanel[3])->getContent();
  if (ip == "FREE")
    return (false);
  else
    return (true);
}
