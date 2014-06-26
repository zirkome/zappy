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
  void bct(const std::string &cmd, std::string &msg, Map &map);
  void tna(const std::string &cmd, std::string &msg, Map &map);
  void pnw(const std::string &cmd, std::string &msg, Map &map);
  void ppo(const std::string &cmd, std::string &msg, Map &map);
  void plv(const std::string &cmd, std::string &msg, Map &map);
  void pin(const std::string &cmd, std::string &msg, Map &map);
  void pex(const std::string &cmd, std::string &msg, Map &map);
  void pbc(const std::string &cmd, std::string &msg, Map &map);
  void pic(const std::string &cmd, std::string &msg, Map &map);
  void pie(const std::string &cmd, std::string &msg, Map &map);
  void pfk(const std::string &cmd, std::string &msg, Map &map);
  void pdr(const std::string &cmd, std::string &msg, Map &map);
  void pgt(const std::string &cmd, std::string &msg, Map &map);
  void pdi(const std::string &cmd, std::string &msg, Map &map);
  void enw(const std::string &cmd, std::string &msg, Map &map);
  void eht(const std::string &cmd, std::string &msg, Map &map);
  void ebo(const std::string &cmd, std::string &msg, Map &map);
  void edi(const std::string &cmd, std::string &msg, Map &map);
  void sgt(const std::string &cmd, std::string &msg, Map &map);
  void seg(const std::string &cmd, std::string &msg, Map &map);
  void smg(const std::string &cmd, std::string &msg, Map &map);
  void suc(const std::string &cmd, std::string &msg, Map &map);
  void sbp(const std::string &cmd, std::string &msg, Map &map);

  std::map<std::string, parseFunc> _func;
};

#endif /* _PROTOCOL_HPP_ */
