#ifndef _CONNECTWIDGET_HPP_
# define _CONNECTWIDGET_HPP_

# include "AWidget.hpp"

class	ConnectWidget : public AWidget
{
public:
  ConnectWidget(int x, int y, int height, int width, const std::string &texture);
  ~ConnectWidget();

  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock);

  void	onClick(Menu &menu);
};

#endif
