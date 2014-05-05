#ifndef _AOBJECT_HPP_
# define _AOBJECT_HPP_

# include <Clock.hh>
# include <Input.hh>
# include <BasicShader.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

class AObject
{
public:
  AObject();
  virtual ~AObject();

  virtual bool initialize() = 0;
  virtual void update(gdl::Clock const &, gdl::Input &) = 0;
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;

  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
  const glm::mat4 getTransformation() const;

protected:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
};

#endif /* _AOBJECT_HPP_ */
