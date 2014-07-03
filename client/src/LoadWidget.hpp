#ifndef _LOADWIDGET_H_
# define _LOADWIDGET_H_

# include "TextImgWidget.hpp"
# include "Menu.hpp"

class	LoadWidget : public TextImgWidget
{
public:
  LoadWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text, int id);
  ~LoadWidget();

  virtual bool	isClicked(int x, int y);
  virtual void	onDisplay(const std::list<std::string> &text, int filePos);
  virtual void	onClick(Menu &menu);

protected:
  int		_id;
};

#endif /* _LOADWIDGET_H_ */
