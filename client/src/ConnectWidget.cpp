#include "Menu.hpp"
#include "ConnectWidget.hpp"

ConnectWidget::ConnectWidget(int x, int y, int height, int width, const std::string &texture, const std::string &textureHover)
  : TextImgWidget(x, y, height, width, texture, textureHover, "Connect")
{
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
