#include <iterator>
#include "Settings.hpp"

Settings::Settings()
{
  _actionList.push_back("forward");
  _actionList.push_back("back");
  _actionList.push_back("left");
  _actionList.push_back("right");

  _cvarList.push_back(new t_cvar ("com_maxFps", 2, 300, 60));
  _cvarList.push_back(new t_cvar ("cg_fov", 20, 180, 80));
  _cvarList.push_back(new t_cvar ("r_windowHeight", 480, 1440, 600));
  _cvarList.push_back(new t_cvar ("r_windowWidth", 640, 2560, 1024));
  _cvarList.push_back(new t_cvar ("m_mapHeight", 5, 100000, 25));
  _cvarList.push_back(new t_cvar ("m_mapWidth", 5, 100000, 25));
  _cvarList.push_back(new t_cvar ("s_mapDensity", 0, 100, 25));
  _cvarList.push_back(new t_cvar ("s_mapLinear", 0, 100, 25));
  _cvarList.push_back(new t_cvar ("r_fullScreen", 0, 1, 0));
  _cvarList.push_back(new t_cvar ("r_mipmap", 0, 1, 1));
  _cvarList.push_back(new t_cvar ("s_fireSpeed", 0, 100000, 10));
  _cvarList.push_back(new t_cvar ("s_fireTime", 0, 1000000, 10));
  _cvarList.push_back(new t_cvar ("r_depthView", 5, 100, 10));
  _cvarList.push_back(new t_cvar ("r_drawFog", 0, 1, 0));
  _cvarList.push_back(new t_cvar ("r_drawLight", 0, 1, 0));
  _cvarList.push_back(new t_cvar ("r_skyBox", 0, 1, 1));
  _cvarList.push_back(new t_cvar ("r_crazyChicken", 0, 1, 0));
  _cvarList.push_back(new t_cvar ("s_mute", 0, 1, 0));

  _speKeys["CAPSLOCK"] = SDLK_CAPSLOCK;
  _speKeys["SPACE"] = SDLK_SPACE;

  _speKeys["F1"] = SDLK_F1;
  _speKeys["F2"] = SDLK_F2;
  _speKeys["F3"] = SDLK_F3;
  _speKeys["F4"] = SDLK_F4;
  _speKeys["F5"] = SDLK_F5;
  _speKeys["F6"] = SDLK_F6;
  _speKeys["F7"] = SDLK_F7;
  _speKeys["F8"] = SDLK_F8;
  _speKeys["F9"] = SDLK_F9;
  _speKeys["F10"] = SDLK_F10;
  _speKeys["F11"] = SDLK_F11;
  _speKeys["F12"] = SDLK_F12;

  _speKeys["KP_0"] = SDLK_KP_0;
  _speKeys["KP_1"] = SDLK_KP_1;
  _speKeys["KP_2"] = SDLK_KP_2;
  _speKeys["KP_3"] = SDLK_KP_3;
  _speKeys["KP_4"] = SDLK_KP_4;
  _speKeys["KP_5"] = SDLK_KP_5;
  _speKeys["KP_6"] = SDLK_KP_6;
  _speKeys["KP_7"] = SDLK_KP_7;
  _speKeys["KP_8"] = SDLK_KP_8;
  _speKeys["KP_9"] = SDLK_KP_9;
  _speKeys["KP_POINT"] = SDLK_PERIOD;

  _speKeys["UPARROW"] = SDLK_UP;
  _speKeys["RIGHTARROW"] = SDLK_RIGHT;
  _speKeys["DOWNARROW"] = SDLK_DOWN;
  _speKeys["LEFTARROW"] = SDLK_LEFT;

  _speKeys["KP_PLUS"] = SDLK_KP_PLUS;
  _speKeys["KP_MINUS"] = SDLK_KP_MINUS;
  _speKeys["KP_DIV"] = SDLK_KP_DIVIDE;
  _speKeys["KP_MULT"] = SDLK_KP_MULTIPLY;
  _speKeys["KP_ENTER"] = SDLK_KP_ENTER;
  _speKeys["KP_NUMLOCK"] = SDLK_NUMLOCKCLEAR;
  _speKeys["KP_PGDN"] = SDLK_PAGEDOWN;
  _speKeys["KP_PGUP"] = SDLK_PAGEUP;
  _speKeys["KP_PRINTSCREEN"] = SDLK_PRINTSCREEN;
  _speKeys["KP_END"] = SDLK_END;
  _speKeys["KP_INSERT"] = SDLK_INSERT;

  _speKeys["LCTRL"] = SDLK_LCTRL;
  _speKeys["LSHIFT"] = SDLK_LSHIFT;
  _speKeys["LALT"] = SDLK_LALT;
  _speKeys["RCTRL"] = SDLK_RCTRL;
  _speKeys["RSHIFT"] = SDLK_RSHIFT;
  _speKeys["RALT"] = SDLK_RALT;

  initCvar();
}

Settings::~Settings()
{
  _keyMap.clear();
}

int	Settings::toNumber(const std::string &str) const
{
  int	num;
  std::istringstream(str) >> num;

  return (num);
}

bool	Settings::isAscii(const std::string &str) const
{
  return (str.size() == 1);
}

void	Settings::initCvar()
{
  v_cvarit	listit;
  v_cvarit	listend = _cvarList.end();

  for (listit = _cvarList.begin(); listit != listend; ++listit)
    {
      _cvarMap.insert(std::pair<cvar, int>
		      (static_cast<cvar>(std::distance(_cvarList.begin(), listit)),
		       (*listit)->default_value));
    }
}

bool	Settings::addCvar(const std::string tab[3])
{
  v_cvarit	listit;
  v_cvarit	listend = _cvarList.end();
  int		cvarValue = toNumber(tab[2]);

  for (listit = _cvarList.begin(); listit != listend; ++listit)
    {
      if ((*listit)->name == tab[1])
	{
	  if (cvarValue > (*listit)->max_value || cvarValue < (*listit)->min_value)
	      cvarValue = (*listit)->default_value;
	  _cvarMap[static_cast<cvar>(std::distance(_cvarList.begin(), listit))] = cvarValue;
	  return (true);
	}
    }
  return (false);
}

/*
** Getters for config files
** As I throw an exception, a try/catch block will be needed
*/

const std::string	&Settings::getCodeFromKey(SDL_Keycode key) const
{
  m_keyCit	it = _speKeys.begin();

  for (m_keyCit end = _speKeys.end(); it != end; ++it)
    {
      if (it->second == key)
	return (it->first);
    }
  throw(Exception("Key not registered"));
  return (it->first);
}

Keycode	Settings::getKeyFromCode(const std::string &str) const
{
  m_keyCit	it = _speKeys.find(str);

  return ((it == _speKeys.end()) ? UNKNOWN_KEY : it->second);
}

bool		Settings::addKey(const std::string tab[3])
{
  v_instit	listit;
  v_instit	listend = _actionList.end();
  int		boundkey;

  for (listit = _actionList.begin(); listit != listend; ++listit)
    {
      if (*listit == tab[2])
	{
	  if (isAscii(tab[1]))
	    _keyMap.insert(std::pair<Keycode, eAction>
			   (tab[1].at(0), static_cast<eAction>
			    (std::distance(_actionList.begin(), listit))));
	  else if ((boundkey = getKeyFromCode(tab[1])) != UNKNOWN_KEY)
	    _keyMap.insert(std::pair<Keycode, eAction>
			   (boundkey, static_cast<eAction>
			    (std::distance(_actionList.begin(), listit))));
	  return (true);
	}
    }
  return (false);
}

void	Settings::parsInst(const std::vector<std::string> &inst)
{
  v_instCit	it = inst.begin();
  v_instCit	end = inst.end();
  std::string	tab[3];

  while (it != end)
    {
      std::istringstream iss(*it);
      for (int i = 0; i < 3; ++i)
	if (!(iss >> tab[i]))
	  {
	    std::cerr << "Missing arguments for " << tab[0] << std::endl;
	    break ;
	  }
      if (tab[0] == "bind")
	addKey(tab);
      else if (tab[0] == "set")
	addCvar(tab);
      ++it;
    }
}

bool	Settings::readFile(std::vector<std::string> &inst,
			   const std::string &filename)
{
  std::ifstream file(filename.c_str());
  std::string	line;

  if (file.is_open())
    {
      while (std::getline(file, line))
	{
	  if (line.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
	    inst.push_back(line);
	}
      file.close();
      return (true);
    }
  else
    std::cerr << "Can't open file " << filename << std::endl;
  return (false);
}

bool	Settings::loadFile(const std::string &filename)
{
  std::vector<std::string>	inst;

  if (readFile(inst, filename) == true)
    parsInst(inst);
  else
    return (false);
  return (true);
}

bool	Settings::cvarExist(cvar var) const
{
  return (_cvarMap.find(var) != _cvarMap.end());
}

/*
** On the methode below, iterator 'it' would never be equal to map.end()
** if cvarExist is used.
*/

int	Settings::getVar(cvar var) const
{
  std::map<cvar, int>::const_iterator	it;

  if ((it = _cvarMap.find(var)) == _cvarMap.end())
    throw(Exception("No such cvar"));
  return (it->second);
}

void	Settings::setVar(cvar var, int value)
{
  _cvarMap[var] = value;
}

eAction	Settings::getActionFromKey(Keycode key) const
{
  std::map<Keycode, eAction>::const_iterator   it;

  if ((it = _keyMap.find(key)) == _keyMap.end())
    return (UNKNOWN);
  return (it->second);
}

/*
** getKeyFromAct Will fill a vector of key and return the number of key inserted
** A vector must be used considering we handle multibinding
*/

int	Settings::getKeyFromAct(eAction act, std::vector<Keycode> &keySet) const
{
  std::map<Keycode, eAction>::const_iterator   it;
  std::map<Keycode, eAction>::const_iterator   end;
  int	nbKey = 0;

  for (it = _keyMap.begin(), end = _keyMap.end(); it != end; ++it)
    {
      if (it->second == act)
	{
	  keySet.push_back(it->first);
	  ++nbKey;
	}
    }
  return (nbKey);
}

void	Settings::setKey(Keycode key, eAction act)
{
  _keyMap[key] = act;
}
