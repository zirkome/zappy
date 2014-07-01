#include <Clock.hh>
#include "Text.hpp"

Text::Text()
  : ATransformation()
{
  _geometry = NULL;
  _defX = 0.0f;
  _defY = 0.0f;
  _defSize = 40.0f;
}

Text::~Text()
{
  if (_geometry)
    delete _geometry;
}

void	Text::initialize()
{
  if (_font.load(FONT) == false)
    throw(Exception("Can't load font"));
}

void	Text::clear()
{
  if (_geometry)
    {
      delete _geometry;
      _geometry = NULL;
    }
}

void	Text::draw(gdl::AShader &shader, gdl::Clock const&) const
{
  if (_geometry)
    {
      _font.bind();
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
    }
}

void	Text::setText(std::string const& str, float x, float y, float size)
{
  float Letterx, Lettery;
  float	space = 0;

  clear();
  if (!str.length())
    return ;
  _geometry = new gdl::Geometry();

  for (unsigned int i = 0; i < str.length(); ++i)
    {
      if (i > 0.5f)
	space = (i - (0.5f * i)) * size;
      Letterx = ((str[i] % 16) - 32 % 16) / 16.0f;
      Lettery = ((str[i] / 16) - 32 / 16) / 16.0f;

      _geometry->pushVertex(glm::vec3(x + space, y + size, 0));
      _geometry->pushVertex(glm::vec3(x + space + size, y + size, 0));
      _geometry->pushVertex(glm::vec3(x + space, y, 0));
      _geometry->pushUv(glm::vec2(Letterx, 1.0f - Lettery));
      _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - Lettery));
      _geometry->pushUv(glm::vec2(Letterx, 1.0f - (Lettery + 1.0f / 16.0f)));

      _geometry->pushVertex(glm::vec3(x + space + size, y + size, 0));
      _geometry->pushVertex(glm::vec3(x + space, y, 0));
      _geometry->pushVertex(glm::vec3(x + space + size, y, 0));
      _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - Lettery));
      _geometry->pushUv(glm::vec2(Letterx, 1.0f - (Lettery + 1.0f / 16.0f)));
      _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - (Lettery + 1.0f / 16.0f)));
    }
  _geometry->build();
}
