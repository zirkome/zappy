#include "Camera.hpp"

Camera::Camera(Settings &set)
  : _pos(0.0, 0.0, 0.0), _pos_view(0.0, 0.0, 1.0), _dir(0.0, 1.0, 0.0)
{
  _projection = glm::perspective(static_cast<float>(set.getVar(FOV)),
				 static_cast<float>(set.getVar(W_WIDTH))
				 / static_cast<float>(set.getVar(W_HEIGHT)),
				 0.1f, 100.0f);
}


Camera::~Camera()
{

}

void	Camera::lookAt()
{
  _transformation = glm::lookAt(_pos, _pos_view, _dir);
}

void	Camera::translate(glm::vec3 vec)
{
  _pos += vec;
  _pos_view += vec;
}

const glm::mat4 &Camera::getTransformation() const
{
  return (_transformation);
}

const glm::mat4	&Camera::getProjection() const
{
  return (_projection);
}

void	Camera::setPointView(glm::vec3 vec)
{
  _pos_view = vec;
}

const glm::vec3	&Camera::getPosView() const
{
  return (_pos_view);
}

void	Camera::setPos(glm::vec3 pos)
{
  _pos = pos;
}

void	Camera::tranlate(glm::vec3 vec)
{
  _pos += vec;
  _pos_view += vec;
}

void	Camera::update(Input in, gdl::Clock clock)
{
  if (in.isPressed(SDLK_w))
    translate(glm::vec3(0.0, 0.0, -1.0) * static_cast<float>(5 * clock.getElapsed()));
  if (in.isPressed(SDLK_s))
    translate(glm::vec3(0.0, 0.0, 1.0) * static_cast<float>(5 * clock.getElapsed()));
  if (in.isPressed(SDLK_d))
    translate(glm::vec3(1.0, 0.0, 0.0) * static_cast<float>(5 * clock.getElapsed()));
  if (in.isPressed(SDLK_a))
    translate(glm::vec3(-1.0, 0.0, 0.0) * static_cast<float>(5 * clock.getElapsed()));
  if (in.isPressed(SDLK_SPACE))
    translate(glm::vec3(0.0, 1.0, 0.0) * static_cast<float>(5 * clock.getElapsed()));
  if (in.isPressed(SDLK_c))
    translate(glm::vec3(0.0, -1.0, 0.0) * static_cast<float>(5 * clock.getElapsed()));
}
