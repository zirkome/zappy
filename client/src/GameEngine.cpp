#include "GameEngine.hpp"
#include "Input.hpp"

GameEngine::GameEngine(GNetwork *socket, gdl::SdlContext *win,
		       Settings *set, Input *input)
  : _socket(socket), _win(win), _set(set), _input(input), _ground(GROUND_TEXTURE),
    _loading(LOADING_TEXTURE), _resources(64, NULL), _cam(*_set)
{
  _display.loading = true;
}

GameEngine::~GameEngine()
{
  delete _resources[FOOD];
  delete _resources[LINEMATE];
  delete _resources[DERAUMERE];
  delete _resources[SIBUR];
  delete _resources[MENDIANE];
  delete _resources[PHIRAS];
  delete _resources[THYSTAME];
}

bool GameEngine::initialize()
{
  if (!_ground.initialize())
    return (false);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER)
      || !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER)
      || !_textShader.build())
    return (false);
  _cam.translate(glm::vec3(0.0, 5.0, 15.0));
  _cam.setPointView(glm::vec3(0.0, 0.0, 10.0));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_loading.initialize())
    return (false);
  _ground.translate(glm::vec3(0.0, -0.5, 0.0));
  _loading.setPos(0, 0);
  _loading.setSize(_set->getVar(W_WIDTH), _set->getVar(W_HEIGHT));
  _loading.fillGeometry();
  _resources[FOOD] = new Model();
  _resources[LINEMATE] = new Model();
  _resources[DERAUMERE] = new Model();
  _resources[SIBUR] = new Model();
  _resources[MENDIANE] = new Model();
  _resources[PHIRAS] = new Model();
  _resources[THYSTAME] = new Model();
  if (!_resources[FOOD]->load(FOOD_MODEL)
      || !_resources[LINEMATE]->load(LINEMATE_MODEL)
      || !_resources[DERAUMERE]->load(DERAUMERE_MODEL)
      || !_resources[SIBUR]->load(SIBUR_MODEL)
      || !_resources[MENDIANE]->load(MENDIANE_MODEL)
      || !_resources[PHIRAS]->load(PHIRAS_MODEL)
      || !_resources[THYSTAME]->load(THYSTAME_MODEL)
      || !_player.load(PLAYER_MODEL)
      || !_egg.load(EGG_MODEL))
    return (false);
  return (true);
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _cam.lookAt();
  if (!_display.loading)
    {
      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      _shader.bind();
      _shader.setUniform("projection", _cam.getProjection());
      _shader.setUniform("view", _cam.getTransformation());
      _shader.setUniform("nbLight", static_cast<int>(_lights.size()));
      _shader.setUniform("isFog", _set->getVar(R_DRAWFOG));
      _shader.setUniform("isLight", _set->getVar(R_DRAWLIGHT));
      _ground.setPos(glm::vec3(_display.map.getX() / 2.0, -0.5,
				  _display.map.getY() / 2.0));
      _ground.setScale(glm::vec3(_display.map.getX(), 1.0, _display.map.getY()));
      _ground.draw(_shader, _clock);
      for (int x = 0;x < _display.map.getX();++x)
	for (int y = 0;y < _display.map.getY();++y)
	  displayItem(_display.map[x * _display.map.getY() + y], x, y);
      std::list<t_egg *>::const_iterator endEgg = _display.map.getEggEnd();
      for (std::list<t_egg *>::const_iterator it = _display.map.getEggBegin();it != endEgg;++it)
	{
	  _egg.setPos(glm::vec3((*it)->x + 0.5, 0.0, (*it)->y + 0.5));
	  _egg.draw(_shader, _clock);
	}
      std::list<t_player *>::const_iterator endPlayer = _display.map.getPlayerEnd();
      for (std::list<t_player *>::const_iterator it = _display.map.getPlayerBegin();it != endPlayer;++it)
	{
	  _player.setPos(glm::vec3((*it)->x + 0.5, 0.0, (*it)->y + 0.5));
	  _player.setRotation(glm::vec3(0.0, 90 - 90 * (*it)->orient, 0.0));
	  _player.draw(_shader, _clock);
	}
      for (std::list<t_broadcast *>::const_iterator it = _display.map.getBroadcastBegin();it != _display.map.getBroadcastEnd();it++)
	(*it)->line.draw(_shader, _clock);
      glDisable(GL_CULL_FACE);
    }
  else
    {
      float x = _set->getVar(W_WIDTH), y = _set->getVar(W_HEIGHT);

      glDisable(GL_DEPTH_TEST);
      _textShader.bind();
      _textShader.setUniform("projection", glm::ortho(0.0f, x,
						      0.0f, y, -1.0f, 1.0f));
      _textShader.setUniform("view", glm::mat4(1));
      _textShader.setUniform("winX", x);
      _textShader.setUniform("winY", y);
      _loading.draw(_textShader, _clock);
      glEnable(GL_DEPTH_TEST);
    }
  _win->flush();
}

void GameEngine::displayItem(const char flag, int x, int y)
{
  float j = 0;
  float posx = x, posy = y;
  float inter = 0.0;

  if (flag & 1)
    {
      _resources[FOOD]->setPos(glm::vec3(posx + 0.5, 0.10, posy + 0.5));
      _resources[FOOD]->draw(_shader, _clock);
    }
  posx += 0.25;
  posy += 0.10;
  j = 0;
  for (int i = 2;i <= 64;i = i << 1)
    {
      if (flag & i)
	{
	  _resources[i]->setPos(glm::vec3(posx + inter, 0.10,
					  posy + ((j > 2) ? (j - 3.0) * 1.0 / 3.0
						  : j * 1.0 / 3.0)));
	  _resources[i]->draw(_shader, _clock);
	}
      ++j;
      if (j > 2 && inter == 0)
	inter += 0.5;
    }
}


bool GameEngine::update()
{
  double fps = 1000.0f / 60.0f;
  double time;
  t_window win;
  l_Keycit    beg;
  l_Keycit    end;

  _win->updateClock(_clock);
  _socket->update(_display);
  _input->getInput();
  _cam.update(*_input, _clock);
  _display.map.updateBroadcast();
  if (_input->isPressed(SDLK_ESCAPE) || ((*_input)[win] && win.event == WIN_QUIT))
    return (false);
  if (_input->isPressed(SDLK_EQUALS))
    {
      _socket->changeTime(_display.time + CHANGETIME);
      _display.time += CHANGETIME;
    }
  if (_input->isPressed(SDLK_MINUS))
    {
      _socket->changeTime(_display.time - CHANGETIME);
      _display.time -= CHANGETIME;
    }
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  return (true);
}
