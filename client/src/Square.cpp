#include "Square.hpp"

Square::Square()
  : IObject(), _texture(NULL), _geometry(NULL), _file("")
{
  _x = 0;
  _y = 0;
  _sizeX = 0;
  _sizeY = 0;
  _scaleX = 1;
  _scaleY = 1;
}

Square::Square(const std::string &file)
  : IObject(), _texture(NULL), _geometry(NULL), _file(file)
{
  _x = 0;
  _y = 0;
  _sizeX = 0;
  _sizeY = 0;
  _scaleX = 1;
  _scaleY = 1;
}

Square::Square(const Square &cpy)
  : IObject(), _texture(cpy._texture), _geometry(cpy._geometry), _file(cpy._file)
{
  _x = 0;
  _y = 0;
  _sizeX = 0;
  _sizeY = 0;
  _scaleX = 1;
  _scaleY = 1;
}

Square::~Square()
{

}

void Square::setPos(int x, int y)
{
  _x = x;
  _y = y;
}

void Square::setSize(int x, int y)
{
  _sizeX = x;
  _sizeY = y;
}

void Square::setScale(int x, int y)
{
  _scaleX = x;
  _scaleY = y;
}



bool Square::initialize()
{
  if (!_texture)
    {
      _texture = new gdl::Texture();
      if (_file.size() && !_texture->load(_file))
	throw(Exception("Cannot load the texture"));
    }
  return (true);
}

void Square::fillGeometry()
{
  if (_geometry)
    delete _geometry;

  _geometry = new gdl::Geometry();

  _geometry->pushVertex(glm::vec3(_x, _y, 0));
  _geometry->pushVertex(glm::vec3(_x + _sizeX * _scaleX, _y, 0));
  _geometry->pushVertex(glm::vec3(_x + _sizeX * _scaleX, _y + _sizeY * _scaleY, 0));
  _geometry->pushVertex(glm::vec3(_x, _y + _sizeY * _scaleY, 0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));

  _geometry->build();
}

void Square::draw(gdl::AShader &shader, gdl::Clock const &) const
{
  if (_texture)
    _texture->bind();
  if (_geometry)
    _geometry->draw(shader, getTransformation(), GL_QUADS);
}

IObject *Square::clone() const
{
  return (new Square(*this));
}

void Square::setTexture(gdl::Texture *texture)
{
  _texture = texture;
}
