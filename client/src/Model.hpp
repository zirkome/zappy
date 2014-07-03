#ifndef _MODEL_H_
# define _MODEL_H_

# include <Model.hh>
# include <Texture.hh>
# include <string>
# include "IObject.hpp"
# include "Exception.hpp"
# include "Input.hpp"

class		Model: public IObject
{
public:
  Model();
  Model(Model const&);
  virtual ~Model();

  bool		initialize();
  bool		load(std::string const&);

  void		draw(gdl::AShader &, gdl::Clock const&) const;

  void		setTexture(gdl::Texture *);

  IObject	*clone() const;

  gdl::Model	*getModel();

private:
  gdl::Model	*_obj;
};

#endif /* !_MODEL_H_ */
