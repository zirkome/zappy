#ifndef _AWIDGET_HPP_
# define _AWIDGET_HPP_

# include <string>
# include "Text.hpp"
# include "GameEngine.hpp"
# include "Square.hpp"

class	Menu;

class	AWidget
{
protected:
  int		_x;
  int		_y;
  int		_height;
  int		_width;
  Text		_text;
  Square	*_square;

public:
  AWidget(int x, int y, int height, int width);
  virtual ~AWidget() = 0;

  void		draw();
  virtual bool	isClicked(int x, int y);
  virtual void	init(const Settings * const set);
  virtual void	onDisplay(const std::list<std::string> &text, int filePos);
  virtual void	onClick(t_gameinfo &gameInfo, Menu &menu) = 0;
  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock) = 0;

  void		setSquare(Square *);
  Square	*getSquare() const;
  int		getX() const;
  int		getY() const;
  int		getHeight() const;
  int		getWidth() const;
  const Text	&getText() const;
};

#endif
