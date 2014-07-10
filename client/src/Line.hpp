#ifndef _LINE_HPP_
# define _LINE_HPP_

# include <iostream>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <Clock.hh>
# include "IObject.hpp"
# include "Exception.hpp"

class Line : public IObject
{
public:
  Line(float x1, float y1, float x2, float y2);
  Line(const Line &);
  virtual ~Line();
  virtual bool initialize();
  virtual void draw(gdl::AShader &shader, gdl::Clock const &) const;
  virtual IObject *clone() const;
  void setTexture(gdl::Texture *texture);

private:
  glm::vec2	_pos1;
  glm::vec2	_pos2;
  gdl::Geometry *_geometry;
};

#endif /* _LINE_HPP_ */
