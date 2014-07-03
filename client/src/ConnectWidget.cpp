#include "Menu.hpp"
#include "ConnectWidget.hpp"

ConnectWidget::ConnectWidget(int x, int y, int height, int width, const std::string &texture)
  : TextImgWidget(x, y, height, width, texture, "Connect")
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

ConnectWidget::~ConnectWidget()
{
}

bool    ConnectWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	ConnectWidget::onClick(Menu &menu)
{
  menu.launchGame();
}
