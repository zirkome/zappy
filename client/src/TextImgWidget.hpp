#ifndef _TEXTIMGWIDGET_H_
# define _TEXTIMGWIDGET_H_

# include <OpenGL.hh>
# include "TextWidget.hpp"
# include "Menu.hpp"

class	TextImgWidget : public TextWidget
{
public:
  TextImgWidget(int x, int y, int height, int width,
		const std::string &texture,
		const std::string &texture_hover, const std::string &text);
  ~TextImgWidget();

  const std::string	&getContent() const;
  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock);
  void		refresh(int width, int height, float xRatio, float yRatio);

protected:
  std::string	_sentence;
};

#endif /* _TEXTIMGWIDGET_H_ */
