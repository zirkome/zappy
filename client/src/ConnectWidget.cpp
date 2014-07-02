#include "Menu.hpp"
#include "ConnectWidget.hpp"

ConnectWidget::ConnectWidget(int x, int y, int height, int width, const std::string &texture)
  : AWidget(x, y, height, width)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

ConnectWidget::~ConnectWidget()
{
}

void	ConnectWidget::onClick(Menu &menu)
{
  menu.launchGame();
}

void	ConnectWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}
