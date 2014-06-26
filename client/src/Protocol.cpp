#include "Protocol.hpp"

Protocol::Protocol()
{
  _func["BIENVENUE"] = &Protocol::bienvenue;
}

Protocol::~Protocol()
{

}

std::string Protocol::parseCmd(const std::string &cmd, Map &map)
{
  std::string msg("");
  std::stringstream ss(cmd);
  std::string tmp;
  std::map<std::string, parseFunc>::iterator it;

  ss >> tmp;
  for (it = _func.begin();it != _func.end() && it->first != tmp;it++);
  if (it == _func.end())
    return (msg);
  (this->*(it->second))(cmd, msg, map);
  std::cout << "CMD => " << cmd << std::endl;
  std::cout << "MSG => " << msg << std::endl;
  return (msg);
}

void Protocol::bienvenue(const std::string &, std::string &msg, Map &)
{
  msg = "GRAPHICS\n";
}

void Protocol::msz(const std::string &cmd, std::string &msg, Map &map)
{

}
