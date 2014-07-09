#include <cstring>
#include <cctype>
#include "Input.hpp"

Input::Input() : _mutex()
{
  std::memset(&_mouse, 0, sizeof(_mouse));
  std::memset(&_window, 0, sizeof(_window));
  _key = 0;
  _links[SDLK_AMPERSAND] = SDLK_1;
  _links[0xE9] = SDLK_2;
  _links[SDLK_QUOTEDBL] = SDLK_3;
  _links[SDLK_QUOTE] = SDLK_4;
  _links[SDLK_LEFTPAREN] = SDLK_5;
  _links[SDLK_MINUS] = SDLK_6;
  _links[0xE8] = SDLK_7;
  _links[SDLK_UNDERSCORE] = SDLK_8;
  _links[0xE7] = SDLK_9;
  _links[0xE0] = SDLK_0;
}

Input::~Input()
{
}

/*
** Basically, here i transform the key after stocking it because
** It would me a non sense stocking the transformation
** What we care off is just the key pressed
*/

/*
** Seems im obliged to stock the transformation bacause of the links
**
*/

Keycode		Input::toAscii(Keycode key) const
{
  if (key >= SDLK_KP_1 && key <= SDLK_KP_0)
    key = '0' + (key == SDLK_KP_0 ? (key - 10) : key) - SDLK_KP_1 + 1;
  if (!(key >= 0 && key < 128))
    return (-1);
  return (key);
}

void	Input::pressKey(const SDL_Event &event)
{
  Scopelock	<Mutex>sc(_mutex);
  bool		size = false;
  l_Keycit	it;

  if ((size ^= (event.key.keysym.mod & (KMOD_SHIFT | KMOD_CAPS))))
    {
      if (_key < 128 && isalpha(_key))
	_key -= (size * 32);
      else
	{
	  m_Linkcit it;

	  if ((it = _links.find(_key)) != _links.end())
	    _key = it->second;
	}
    }
  if (_key == SDLK_KP_PERIOD)
    _key = '.';
  if ((it = std::find(_keyPressed.begin(), _keyPressed.end(), _key)) == _keyPressed.end())
    _keyPressed.push_back(_key);
}

/*
** Here i need to cehck twice because of the transformations
*/

void	Input::unpressKey()
{
  Scopelock	<Mutex>sc(_mutex);
  bool		size = true;
  l_Keyit	it;
  Keycode      	key;

  key = _key;
  if (key == SDLK_KP_PERIOD)
    key = '.';
  if ((it = std::find(_keyPressed.begin(), _keyPressed.end(), key)) != _keyPressed.end())
    _keyPressed.erase(it);
  if (key < 128 && isalpha(key))
    key -= (size * 32);
  else
    {
      m_Linkcit it;

      if ((it = _links.find(key)) != _links.end())
	key = it->second;
      key = key;
    }
  if ((it = std::find(_keyPressed.begin(), _keyPressed.end(), key)) != _keyPressed.end())
    _keyPressed.erase(it);
}

void	Input::keyboardInput(const SDL_Event &event)
{
  _key = event.key.keysym.sym;
  if (event.type == SDL_KEYDOWN)
    pressKey(event);
  else
    unpressKey();
}

void	Input::mouseInput(const SDL_Event &event)
{
  switch (event.type)
    {
    case SDL_MOUSEMOTION:
      _mouse.x = event.motion.x;
      _mouse.y = event.motion.y;
      _mouse.event = MOTION;
      break ;
    case SDL_MOUSEBUTTONDOWN:
      _mouse.x = event.button.x;
      _mouse.y = event.button.y;
      _mouse.button = event.button.button;
      _mouse.click = event.button.clicks;
      _mouse.event = BUTTONDOWN;
      break ;
    case SDL_MOUSEBUTTONUP:
      if (_mouse.event != BUTTONUP)
	{
	  _mouse.x = event.button.x;
	  _mouse.y = event.button.y;
	  _mouse.event = BUTTONUP;
	}
      else
	_mouse.event = NONE;
      break ;
    case SDL_MOUSEWHEEL:
      _mouse.x = event.wheel.x;
      _mouse.y = event.wheel.y;
      _mouse.event = WHEEL;
      break ;
   default:
      _mouse.event = NONE;
      break ;
    }
}

void	Input::windowEvent(const SDL_Event &event)
{
  switch (event.type)
    {
    case SDL_QUIT:
      _window.event = WIN_QUIT;
      break ;
    }
}

void	Input::getInput()
{
  SDL_Event	event;

  if (_mouse.event != BUTTONDOWN)
    _mouse.event = NONE;
  _window.event = WIN_NONE;
  while (SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
	  keyboardInput(event);
	  break ;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEWHEEL:
	  mouseInput(event);
	  break ;
	case SDL_QUIT:
	  windowEvent(event);
	  break ;
	}
    }
}

bool	Input::operator[](t_mouse &mouse) const
{
  mouse = _mouse;
  if (_mouse.event == NONE)
    return (false);
  return (true);
}

bool	Input::operator[](t_window &win) const
{
  win = _window;
  if (_window.event == WIN_NONE)
    return (false);
  return (true);
}

bool	Input::isPressed(Keycode key)
{
  Scopelock	<Mutex>sc(_mutex);
  l_Keycit it;

  it = std::find(_keyPressed.begin(), _keyPressed.end(), key);
  return (it != _keyPressed.end());
}

const l_Keycit	Input::getPressedBeg() const
{
  return (_keyPressed.begin());
}

const l_Keycit	Input::getPressedEnd() const
{
  return (_keyPressed.end());
}

void	Input::operator[](SDL_Keycode * const key) const
{
  *key = _key;
}
