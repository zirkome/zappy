#include "GameEngine.hpp"
#include "Camera.hpp"

Camera::Camera(): _phi(0.0), _theta(0.0)
{
  _projection = glm::perspective(FOV, DEF_SIZE_X / DEF_SIZE_Y, 0.1f, 100.0f);
}


Camera::~Camera()
{

}

void	Camera::initialize(glm::vec3 pos_cam, glm::vec3 pos_view, glm::vec3 dir_cam)
{
  _pos_cam = pos_cam;
  _pos_view = pos_view;
  _dir = dir_cam;
  lookAt();
}

void	Camera::lookAt()
{
  _transformation = glm::lookAt(_pos_cam, _pos_view, _dir);
}

const glm::mat4 &Camera::getTransformation() const
{
  return (_transformation);
}

const glm::mat4 &Camera::getProjection() const
{
  return (_projection);
}
