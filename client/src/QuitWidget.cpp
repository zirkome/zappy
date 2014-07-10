#include "Menu.hpp"
#include "QuitWidget.hpp"

QuitWidget::QuitWidget(int x, int y, int height, int width, const std::string &texture,
		       const std::string &textureHover)
  : TextImgWidget(x, y, height, width, texture, textureHover, "Quit")
{
}

QuitWidget::~QuitWidget()
{
}

bool    QuitWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	QuitWidget::onClick(Menu &menu)
{
  menu.setDone(true);
}
