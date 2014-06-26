#ifndef _TEXT_H_
# define _TEXT_H_

# include <string>
# include <Texture.hh>
# include <Geometry.hh>
# include <sstream>
# include <Clock.hh>
# include "Exception.hpp"
# include "ATransformation.hpp"

# define FONT "assets/font.tga"

class	Text: public ATransformation
{
public:
  Text();
  virtual ~Text();

  void	initialize();
  void	draw(gdl::AShader &, gdl::Clock const&) const;
  void	clear();

  void	setText(std::string const&, float, float, float);

  template <typename T>
  std::string		operator<<(T const& in)
  {
    std::stringstream	ss;

    ss << in;
    setText(ss.str(), _defX, _defY, _defSize);

    return (ss.str());
  }

private:
  float				_defX;
  float				_defY;
  float				_defSize;

  gdl::Texture			_font;
  gdl::Geometry			*_geometry;
};

#endif /* _TEXT_H_ */
