#include <string>
#include "ModelObject.hpp"

ModelObject::ModelObject(std::string const &path) : _path(path)
{
}

ModelObject::~ModelObject()
{

}

bool ModelObject::initialize()
{
  _speed = 10.0f;
  if (_model.load(_path) == false)
    {
      std::cerr << "Cannot load the " << _path << " object" << std::endl;
      return (false);
    }
  std::cout << "Model loaded" << std::endl;
  return (true);
}

void ModelObject::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_z))
    translate(glm::vec3(0, 1, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_s))
    translate(glm::vec3(0, -1, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_UP))
    translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_DOWN))
    translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_LEFT))
    translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_RIGHT))
    translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void ModelObject::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
