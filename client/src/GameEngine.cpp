#include "GameEngine.hpp"
#include "Input.hpp"

GameEngine::GameEngine(GNetwork *socket, gdl::SdlContext *win): 
  _socket(socket), _win(win), _input(), _ground("./assets/wall.tga")
{
  _display.loading = true;
}

GameEngine::~GameEngine()
{
  _win->stop();
}

bool GameEngine::initialize()
{
  if (!_ground.initialize())
    return (false);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  _cam.translate(glm::vec3(0.0, 5.0, 15.0));
  _cam.setPointView(glm::vec3(0.0, 0.0, 10.0));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // _resources.push_back(new Model());
  return (true);
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _cam.lookAt();
  _shader.bind();
  _shader.setUniform("projection", _cam.getProjection());
  _shader.setUniform("view", _cam.getTransformation());
  _shader.setUniform("nbLight", 0);
  _shader.setUniform("isFog", 0);
  _shader.setUniform("isLight", 0);
  if (!_display.loading)
    {
      _ground.setScale(glm::vec3(_display.map.getX(), -0.5, _display.map.getY()));
      _ground.draw(_shader, _clock);
    }
  else
    {

    }
  _win->flush();
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
  _input.getInput();
  if (_input.isPressed(SDLK_ESCAPE) || (_input[win] && win.event == WIN_QUIT))
    {
      usleep(100000);
      return (false);
    }
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  return (true);
}
