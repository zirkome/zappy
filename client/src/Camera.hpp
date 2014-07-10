#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Clock.hh>
# include "Input.hpp"
# include "Settings.hpp"

class Camera
{
public:
  Camera(Settings &set);
  ~Camera();

  void lookAt();
  void translate(glm::vec3 vec);
  void setPointView(glm::vec3 vec);
  void setPos(glm::vec3 pos);
  void tranlate(glm::vec3 vec);
  void update(Input in, gdl::Clock clock);

  const glm::mat4 &getTransformation() const;
  const glm::mat4 &getProjection() const;
  const glm::vec3 &getPosView() const;

private:
  glm::mat4	_transformation;
  glm::mat4	_projection;
  glm::vec3	_pos;
  glm::vec3	_pos_view;
  glm::vec3	_dir;
};

#endif /* _CAMERA_HPP_ */
