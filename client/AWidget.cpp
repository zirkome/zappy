#include "AWidget.hpp"

AWidget::AWidget(int x, int y, int height, int width)
  : _text()
{
  _x = x;
  _y = y;
  _height = height;
  _width = width;
  _square = NULL;
  try
    {
      _text.initialize();
    }
  catch (const Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return ;
    }
}

AWidget::~AWidget()
{
}

bool	AWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	AWidget::draw()
{
}

void	AWidget::onDisplay(const std::list<std::string> &/*text*/, int /*filePos*/)
{
}

void	AWidget::init(const Settings * const /*set*/)
{
}

void	AWidget::setSquare(Square *square)
{
  _square = square;
}

Square	*AWidget::getSquare() const
{
  return (_square);
}

int	AWidget::getX() const
{
  return (_x);
}

int	AWidget::getY() const
{
  return (_y);
}

int	AWidget::getHeight() const
{
  return (_height);
}

int	AWidget::getWidth() const
{
  return (_width);
}

const Text	&AWidget::getText() const
{
  return (_text);
}
