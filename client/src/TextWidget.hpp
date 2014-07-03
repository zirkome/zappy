#ifndef _TEXTWIDGET_HPP_
# define _TEXTWIDGET_HPP_

# include "AWidget.hpp"
# include "Menu.hpp"
 
class	TextWidget : public AWidget
{
public:
  TextWidget(int x, int y, int height, int width, const std::string &text);
  ~TextWidget();

  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock);
  virtual bool	isClicked(int x, int y);
  virtual void	onClick(Menu &menu);

  void		setText(std::string const& str, float x, float y, float size);
};

#endif
