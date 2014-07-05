#include <iostream>
#include <sstream>
#include "Light.hpp"

Light::Light(int id, eLight type, glm::vec3 color, glm::vec3 pos, float power):
  _id(id), _type(type), _color(color), _pos(pos), _power(power)
{

}

Light::~Light()
{

}

void Light::render(gdl::BasicShader &shader)
{
  std::stringstream ss("");

  ss << _id;
  shader.bind();
  shader.setUniform("light[" + ss.str() + "].type", static_cast<int>(_type));
  shader.setUniform("light[" + ss.str() + "].color", _color);
  shader.setUniform("light[" + ss.str() + "].pos", _pos);
  shader.setUniform("light[" + ss.str() + "].power", _power);
}
