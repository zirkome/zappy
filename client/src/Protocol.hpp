#ifndef _PROTOCOL_HPP_
# define _PROTOCOL_HPP_

# include <map>
# include <iostream>
# include <sstream>
# include "Map.hpp"

typedef struct s_display t_display;

class Protocol
{
  typedef void (Protocol::*parseFunc)(const std::string &, std::string &, t_display &);

public:
  Protocol();
  virtual ~Protocol();

  std::string parseCmd(const std::string &cmd, t_display &info);

private:
  int getNb(const std::string &) const;

  void bienvenue(const std::string &cmd, std::string &msg, t_display &info);
  void msz(const std::string &cmd, std::string &msg, t_display &info);
  void bct(const std::string &cmd, std::string &msg, t_display &info);
  void tna(const std::string &cmd, std::string &msg, t_display &info);
  void pnw(const std::string &cmd, std::string &msg, t_display &info);
  void ppo(const std::string &cmd, std::string &msg, t_display &info);
  void plv(const std::string &cmd, std::string &msg, t_display &info);
  void pin(const std::string &cmd, std::string &msg, t_display &info);
  void pex(const std::string &cmd, std::string &msg, t_display &info);
  void pbc(const std::string &cmd, std::string &msg, t_display &info);
  void pic(const std::string &cmd, std::string &msg, t_display &info);
  void pie(const std::string &cmd, std::string &msg, t_display &info);
  void pfk(const std::string &cmd, std::string &msg, t_display &info);
  void pdr(const std::string &cmd, std::string &msg, t_display &info);
  void pgt(const std::string &cmd, std::string &msg, t_display &info);
  void pdi(const std::string &cmd, std::string &msg, t_display &info);
  void enw(const std::string &cmd, std::string &msg, t_display &info);
  void eht(const std::string &cmd, std::string &msg, t_display &info);
  void ebo(const std::string &cmd, std::string &msg, t_display &info);
  void edi(const std::string &cmd, std::string &msg, t_display &info);
  void sgt(const std::string &cmd, std::string &msg, t_display &info);
  void seg(const std::string &cmd, std::string &msg, t_display &info);
  void smg(const std::string &cmd, std::string &msg, t_display &info);
  void suc(const std::string &cmd, std::string &msg, t_display &info);
  void sbp(const std::string &cmd, std::string &msg, t_display &info);

  std::map<std::string, parseFunc> _func;
};

#endif /* _PROTOCOL_HPP_ */
