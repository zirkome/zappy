#ifndef _IOBJECT_HPP_
# define _IOBJECT_HPP_

# include <Clock.hh>
# include <BasicShader.hh>
# include <Texture.hh>
# include "ATransformation.hpp"

class IObject: public ATransformation
{
public:
  IObject(): ATransformation() {};
  virtual ~IObject() {};

  virtual bool initialize() = 0;
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) const = 0;
  virtual IObject *clone() const = 0;
  virtual void setTexture(gdl::Texture *) = 0;
};

#endif /* _IOBJECT_HPP_ */
