#ifndef _LIGHT_HPP_
# define _LIGHT_HPP_

# include <glm/glm.hpp>
# include <BasicShader.hh>

enum eLight
  {
    SUN = 1,
    SPOT
  };

class Light
{
public:
  Light(int id, eLight type, glm::vec3 color, glm::vec3 pos, float power);
  virtual ~Light();

  void render(gdl::BasicShader &shader);

private:
  int	    _id;
  eLight    _type;
  glm::vec3 _color;
  glm::vec3 _pos;
  float     _power;
};

#endif /* _LIGHT_HPP_ */
