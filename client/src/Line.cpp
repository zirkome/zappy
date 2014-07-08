#include "Line.hpp"

Line::Line(float x1, float y1, float x2, float y2)
  : IObject(), _pos1(x1, y1), _pos2(x2, y2), _geometry(NULL)
{
}

Line::Line(const Line &cpy)
  : IObject(), _pos1(cpy._pos1), _pos2(cpy._pos2), _geometry(cpy._geometry)
{
}


Line::~Line()
{
  delete _geometry;
}

bool Line::initialize()
{
  _geometry = new gdl::Geometry();

  _geometry->pushVertex(glm::vec3(_pos1.x, 1.0, _pos1.y));
  _geometry->pushVertex(glm::vec3(_pos2.x, 1.0, _pos2.y));

  _geometry->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
  _geometry->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

  _geometry->build();
  return (true);
}

void Line::draw(gdl::AShader &shader, gdl::Clock const &) const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  if (_geometry)
    _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}

IObject *Line::clone() const
{
  return (new Line(*this));
}

void Line::setTexture(gdl::Texture *)
{

}
