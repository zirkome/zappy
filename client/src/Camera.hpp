#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# include <glm/glm.hpp>

class Camera
{
public:
  Camera();
  ~Camera();

  void initialize(glm::vec3 pos_cam, glm::vec3 pos_view, glm::vec3 dir_cam);
  void lookAt();
  const glm::mat4 &getTransformation() const;
  const glm::mat4 &getProjection() const;

private:
  glm::mat4	_transformation;
  glm::mat4	_projection;
  glm::vec3	_pos_cam;
  glm::vec3	_pos_view;
  glm::vec3	_dir;
  double	_phi;
  double	_theta;
};

#endif /* _CAMERA_HPP_ */
