#include "GameEngine.hpp"

GameEngine::GameEngine(): _win(), _input()
{

}

GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  if (!_win.start(1600, 900, "-- ZAPPY --"))
    return (false);
  return (true);
}

void GameEngine::draw()
{

}

bool GameEngine::update()
{
  if (_input.getKey(SDLK_ESCAPE))
    return (false);
  sleep(1);
  return (true);
}
