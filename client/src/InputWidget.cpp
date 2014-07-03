#include "Menu.hpp"
#include "InputWidget.hpp"

InputWidget::InputWidget(int x, int y, int height, int width,
			 const std::string &texture, const std::string &text) :
  LoadWidget(x, y, height, width, texture, text, 0)
{
}

InputWidget::~InputWidget()
{
}

void	InputWidget::onDisplay(const std::list<std::string> &/*text*/, int /*filePos*/)
{
}

bool	InputWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	InputWidget::onClick(Menu &menu)
{
  menu.textInput(_sentence, 20);
}
