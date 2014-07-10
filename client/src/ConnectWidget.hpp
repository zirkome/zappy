#ifndef _CONNECTWIDGET_HPP_
# define _CONNECTWIDGET_HPP_

# include "TextImgWidget.hpp"

class	ConnectWidget : public TextImgWidget
{
public:
  ConnectWidget(int x, int y, int height, int width, const std::string &texture,
		const std::string &textureHover = "");
  ~ConnectWidget();

  virtual bool  isClicked(int x, int y);
  void	onClick(Menu &menu);
};

#endif
