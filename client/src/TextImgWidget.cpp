#include "Menu.hpp"
#include "TextImgWidget.hpp"

TextImgWidget::TextImgWidget(int x, int y, int height, int width,
			     const std::string &texture,
			     const std::string &texture_hover,
			     const std::string &text)
  : TextWidget(x, y, height, width, text)
{
  if (texture_hover != "")
    {
      _squareHover = new Square(texture_hover);
      _squareHover->initialize();
      _squareHover->setPos(x, y);
      _squareHover->setSize(width, height);
    }
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
  _sentence = text;
}

TextImgWidget::~TextImgWidget()
{
}

void	TextImgWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  if (_hover && _squareHover != NULL)
    {
      _squareHover->fillGeometry();
      _squareHover->draw(shader, clock);
    }
  else
    {
      _square->fillGeometry();
      _square->draw(shader, clock);
    }
  _text.setText(_sentence,_x +_width / 2 - (_sentence.length() / 4.0) * 45, _y + (_height - 45) / 2, 45);
  glDisable(GL_DEPTH_TEST);
  _text.draw(shader, clock);
  glEnable(GL_DEPTH_TEST);
}

const std::string	&TextImgWidget::getContent() const
{
  return (_sentence);
}
