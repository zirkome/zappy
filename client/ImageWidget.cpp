#include "ImageWidget.hpp"

ImageWidget::ImageWidget(int x, int y, int height, int width, const std::string &texture)
  : AWidget(x, y, height, width)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

ImageWidget::~ImageWidget()
{
}

bool	ImageWidget::isClicked(int /*x*/, int /*y*/)
{
  return (false);
}

void	ImageWidget::onClick(t_gameinfo &/*gameInfo*/, Menu &/*menu*/)
{
}

void	ImageWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}
