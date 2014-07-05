#ifndef _QUITWIDGET_HPP_
# define _QUITWIDGET_HPP_

# include "TextImgWidget.hpp"

class	QuitWidget : public TextImgWidget
{
public:
  QuitWidget(int x, int y, int height, int width, const std::string &texture);
  ~QuitWidget();

  virtual bool  isClicked(int x, int y);
  void	onClick(Menu &menu);
};

#endif
