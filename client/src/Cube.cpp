#include "Cube.hpp"

Cube::Cube()
{

}

Cube::~Cube()
{

}

bool Cube::initialize()
{
  _speed = 10.0f;
  if (_texture.load("./assets/texture.tga") == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }

  _geometry.pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry.pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry.pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry.pushVertex(glm::vec3(-1.0, -1.0, 1.0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry.pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0, -1.0, -1.0));

  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));

  _geometry.pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry.pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry.pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry.pushVertex(glm::vec3(1.0, -1.0, 1.0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry.pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry.pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0, -1.0, -1.0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry.pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0, 1.0, 1.0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry.pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry.pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry.pushVertex(glm::vec3(-1.0, -1.0, -1.0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

void Cube::update(gdl::Clock const &clock, gdl::Input &input)
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

void Cube::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
