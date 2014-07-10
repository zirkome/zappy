#ifndef _INPUTWIDGET_H_
# define _INPUTWIDGET_H_

# include "TextImgWidget.hpp"
# include "Menu.hpp"

class InputWidget : public TextImgWidget
{
public:
  InputWidget(int x, int y, int height, int width,
	      const std::string &texture, const std::string &text,
	      const std::string &textureHover = "");
  ~InputWidget();

  void	onDisplay(const std::list<std::string> &text, int file);
  bool	isClicked(int x, int y);
  virtual void	onClick(Menu &menu);
};

#endif /* _INPUTWIDGET_H_ */
