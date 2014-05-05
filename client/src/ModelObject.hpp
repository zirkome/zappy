#ifndef _MODELOBJECT_HPP_
# define _MODELOBJECT_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Model.hh>
# include <Texture.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SDL_keycode.h>
# include <iostream>
# include <string>
# include "AObject.hpp"

class ModelObject : public AObject
{
public:
  ModelObject(std::string const &);
  virtual ~ModelObject();
  virtual bool initialize();
  virtual void update(gdl::Clock const &clock, gdl::Input &input);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &);

private:
  gdl::Model		_model;
  const std::string	&_path;
  float _speed;
};

#endif /* _MODELOBJECT_HPP_ */
