#include <algorithm>
#include "Console.hpp"
#include "Settings.hpp"

Console::Console(Settings &set, Input &input, gdl::Clock &clock, gdl::AShader &shader):
  _set(set), _input(input), _clock(clock), _shader(shader)
{
  _buf = "";
  _ret = "";
  _cmd["bind"] = &Console::bind;
  _cmd["set"] = &Console::set;
  _cmd["help"] = &Console::help;
  _cmd["import"] = &Console::import;
}

void	Console::print(Text &text, int winY)
{
  int	y = 1;

  text.setText(_buf, 20, 0, POLICE_SIZE);
  text.draw(_shader, _clock);
  for (int size = _history.size(); size > (winY / POLICE_SIZE); --size)
    _history.pop_back();
  for (std::list<std::string>::iterator it = _history.begin(); it != _history.end(); ++it)
    {
      text.setText(*it, 20, y * POLICE_SIZE, POLICE_SIZE);
      text.draw(_shader, _clock);
      ++y;
    }
}

void	Console::handleClock(const gdl::SdlContext &win, int &frame,
			     double &time, double fps)
{
  time = _clock.getElapsed();
  if (time < fps)
    usleep((fps - time) * 1000);
  frame = (frame >= 100) ? 100 : frame + 1;
  win.updateClock(_clock);
}

bool	Console::aff(const gdl::SdlContext &win, float winX, float winY)
{
  Text		text;
  double	fps = 1000.0 / 25.0;
  int		frame = -1;
  double	time;
  Keycode	key = 0;
  Keycode	save = -1;

  text.initialize();
  _buf.clear();
  _buf.push_back('>');
  _shader.bind();
  _shader.setUniform("projection", glm::ortho(0.0f, static_cast<float>(_set.getVar(W_WIDTH)),
					      0.0f, static_cast<float>(_set.getVar(W_HEIGHT)),
					      -1.0f, 1.0f));
  _shader.setUniform("view", glm::mat4(1));
  _shader.setUniform("winX", winX);
  _shader.setUniform("winY", winY);
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
	  if (save == key)
	    {
	      if (((key < 128 && key != '\b') && frame < 8) ||
		  (key == '\b' && frame < 2) ||
		  ((key == '\r' || key == SDLK_KP_ENTER) && frame < 15))
		{
		  handleClock(win, frame, time, fps);
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
	{
	  if (key == '\r' || key == SDLK_KP_ENTER)
	    {
	      _buf.erase(_buf.begin());
	      if (_buf == "quit")
		return (true);
	      parseCmd(_buf, _ret);
	      _ret = _buf + ":" + _ret;
	      _history.push_front(_ret);
	      _buf.clear();
	      _buf.push_back('>');
	    }
	  else if (key > 0 && key < 128)
	    {
	      if (key == '\b' && _buf.length() > 1)
		_buf = _buf.substr(0, _buf.length() - 1);
	      if (isPrintable(key) == true)
		_buf.push_back(static_cast<char>(key));
	    }
	}
      print(text, static_cast<int>(winY));
      win.flush();
      handleClock(win, frame, time, fps);
    }
  return (true);
}

bool	Console::isPrintable(char key)
{
  if (key >= ' ' && key <= '~')
    return (true);
  return (false);
}

bool	Console::import(const std::string &arg, std::string &ret, int nbr_space)
{
  if (nbr_space == 1)
    {
      if (_set.loadFile(arg) == true)
	{
	  ret = "Successfully imported " + arg + ".";
	  return (true);
	}
      else
	{
	  ret = "Failed to import : " + arg;
	  return (false);
	}
    }
  ret = "Failed to import : " + arg + " : not enough arguments.";
  return (false);
}

bool	Console::bind(const std::string &arg, std::string &ret, int nbr_space)
{
  std::string	tab[3];

  if (nbr_space < 2)
    {
      ret = "bind " + arg + " : not enough arguments.";
      return (false);
    }
  tab[0] = "bind";
  tab[1] = arg.substr(0, arg.find_first_of(' ', 0));
  tab[2] = arg.substr(arg.find_first_of(' ', 0) + 1, arg.length());
  if (_set.addKey(tab) == false)
    {
      ret = arg + " : failed to bind " + arg + ".";
      return (false);
    }
  ret = "Success.";
  return (true);
}

bool	Console::set(const std::string &arg, std::string &ret, int nbr_space)
{
  std::string	tab[3];

  if (nbr_space < 2)
    {
      ret = arg + " not enough arguments.";
      return (false);
    }
  tab[0] = "set";
  tab[1] = arg.substr(0, arg.find_first_of(' ', 0));
  tab[2] = arg.substr(arg.find_first_of(' ', 0) + 1, arg.length());
  if (_set.addCvar(tab) == false)
    {
      ret = arg + " failed to set " + arg + ".";
      return (false);
    }
  ret = "Success.";
  return (true);
}

bool	Console::help(const std::string &/*arg*/, std::string &ret, int /*nbr_space*/)
{
  ret = "You can configure manually some features and options about the game.\n";
  ret += "You can bind a cvar using this syntax : \"bind cvar value\".\n";
  ret += "You can set a key using this syntax : \"set key action\".\n";
  ret += "You can import a config file using this syntax : \"import filename\".";
  return (true);
}

bool	Console::parseCmd(const std::string &cmdline, std::string &ret)
{
  std::string	cmd;
  std::string	arg("");
  bool		(Console::*ptr)(const std::string &, std::string &, int);
  int		nbr_space = std::count(cmdline.begin(), cmdline.end(), ' ');

  if (nbr_space > 0)
    {
      cmd = cmdline.substr(0, cmdline.find_first_of(' ', 0));
      arg = cmdline.substr(cmdline.find_first_of(' ', 0) + 1, cmdline.length());
    }
  else
    cmd = cmdline;
  if (_cmd.find(cmd) == _cmd.end())
    {
      ret = ": unknown command.";
      return (false);
    }
  if (nbr_space > 2)
    {
      ret = ": too many arguments.";
      return (false);
    }
  ptr = _cmd[cmd];
  return (this->*ptr)(arg, ret, nbr_space);
}

Console::~Console()
{
  ;
}
