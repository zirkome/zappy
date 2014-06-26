#ifndef _PROTOCOL_HPP_
# define _PROTOCOL_HPP_

# include <map>
# include <iostream>
# include <sstream>
# include "Map.hpp"

class Protocol
{
  typedef void (Protocol::*parseFunc)(const std::string &, std::string &, Map &);

public:
  Protocol();
  virtual ~Protocol();

  std::string parseCmd(const std::string &cmd, Map &map);

private:
  void bienvenue(const std::string &cmd, std::string &msg, Map &map);
  void msz(const std::string &cmd, std::string &msg, Map &map);

  std::map<std::string, parseFunc> _func;
};

#endif /* _PROTOCOL_HPP_ */
