#ifndef _GNETWORK_HPP_
# define _GNETWORK_HPP_

# include <iostream>
# include <libsocket.h>
# include "Exception.hpp"
// # include "Map.hpp"

class GNetwork
{
public:
  GNetwork();
  virtual ~GNetwork();

  bool open(const std::string &ip, const std::string &port);
  bool close();

  void update(/* Map &map */);

private:
  int		_fd;
  t_ringb	_buffer;
};

#endif /* _GNETWORK_HPP_ */
