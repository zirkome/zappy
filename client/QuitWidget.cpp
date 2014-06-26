#include "QuitWidget.hpp"

QuitWidget::QuitWidget(int x, int y, int height, int width, const std::string &texture)
  : AWidget(x, y, height, width)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

QuitWidget::~QuitWidget()
{
}

void	QuitWidget::onClick(t_gameinfo &/*gameInfo*/, Menu &menu)
{
  menu.setDone(true);
}

void	QuitWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}
