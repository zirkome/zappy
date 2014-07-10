#include "Menu.hpp"
#include "InputWidget.hpp"

InputWidget::InputWidget(int x, int y, int height, int width,
			 const std::string &texture, const std::string &text,
			 const std::string &textureHover) :
  TextImgWidget(x, y, height, width, texture, textureHover, text)
{
}

InputWidget::~InputWidget()
{
}

void	InputWidget::onDisplay(const std::list<std::string> &text, int filePos)
{
  std::list<std::string>::const_iterator it = text.begin();
  std::list<std::string>::const_iterator end = text.end();

  for (int count = 0; it != end; ++it, ++count)
    {
      if (count == filePos * 4)
	{
	  _sentence = *it;
	  return ;
	}
    }
  _sentence = "FREE";
}

bool	InputWidget::isClicked(int x, int y)
{
  if (_sentence != "FREE" && x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	InputWidget::onClick(Menu &menu)
{
  menu.textInput(_sentence, 20);
}
