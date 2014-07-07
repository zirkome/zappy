#ifndef _GNETWORK_HPP_
# define _GNETWORK_HPP_

# include <iostream>
# include <queue>
# include <sys/time.h>
# include <libsocket.h>
# include "Exception.hpp"
# include "Map.hpp"
# include "Protocol.hpp"

typedef s_display t_display;

class GNetwork
{
public:
  GNetwork();
  virtual ~GNetwork();

  bool open(const std::string &ip, const std::string &port);
  bool close();
  void send(const std::string &msg);

  void changeTime(int t);

  void update(t_display &map);

private:
  int			  _fd;
  t_ringb		  *_buffer;
  std::queue<std::string> _msg;
  Protocol		  _proto;
};

#endif /* _GNETWORK_HPP_ */
