#include "GameEngine.hpp"

GameEngine::GameEngine(GNetwork *socket): _win(), _input(), _cube("./assets/wall.tga"),
					  _socket(socket)
{
  _isPlaying = false;
}

GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  if (!_win.start(1600, 900, "-- Zappy --"))
    return (false);
  if (!_cube.initialize())
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
  _cube.draw(_shader, _clock);
  _win.flush();
}

bool GameEngine::update()
{
  double fps = 1000.0f / 60.0f;
  double time;

  _win.updateInputs(_input);
  _win.updateClock(_clock);
  _socket->update();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return (false);
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  return (true);
}
