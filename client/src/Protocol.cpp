#include "Protocol.hpp"

Protocol::Protocol()
{
  _func["BIENVENUE"] = &Protocol::bienvenue;
  _func["msz"] = &Protocol::msz;
  _func["bct"] = &Protocol::bct;
  _func["tna"] = &Protocol::tna;
  _func["pnw"] = &Protocol::pnw;
  _func["ppo"] = &Protocol::ppo;
  _func["plv"] = &Protocol::plv;
  _func["pin"] = &Protocol::pin;
  _func["pex"] = &Protocol::pex;
  _func["pbc"] = &Protocol::pbc;
  _func["pic"] = &Protocol::pic;
  _func["pie"] = &Protocol::pie;
  _func["pfk"] = &Protocol::pfk;
  _func["pdr"] = &Protocol::pdr;
  _func["pgt"] = &Protocol::pgt;
  _func["pdi"] = &Protocol::pdi;
  _func["enw"] = &Protocol::enw;
  _func["eht"] = &Protocol::eht;
  _func["ebo"] = &Protocol::ebo;
  _func["edi"] = &Protocol::edi;
  _func["sgt"] = &Protocol::sgt;
  _func["seg"] = &Protocol::seg;
  _func["smg"] = &Protocol::smg;
  _func["suc"] = &Protocol::suc;
  _func["sbp"] = &Protocol::sbp;
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

void Protocol::msz(const std::string &cmd, std::string &, Map &map)
{
  std::stringstream ss(cmd);
  int x, y;
  std::string tmp;

  ss >> tmp >> x >> y;
  map.createMap(x, y);
}

void Protocol::bct(const std::string &cmd, std::string &, Map &map)
{
  std::stringstream ss(cmd);
  std::string tmp;
  int x, y;
  int q[6];

  try
    {
      ss >> tmp >> x >> y;
      for (int i = 0;i < 6;++i)
	ss >> q[i];
      map[x * y] = 0;
      for (int i = 1, j = 0;i <= 64;i = i << 1, j++)
	if (q[j] > 0)
	  map[x * y] |= i;
      map.display();
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void Protocol::tna(const std::string &cmd, std::string &, Map &map)
{

}

void Protocol::pnw(const std::string &cmd, std::string &, Map &map)
{
  std::stringstream ss(cmd);
  std::stringstream parse("");
  int nb, x, y, lvl, orient;
  std::string team;

  if (!(ss >> team >> team) || team.empty() || team[0] != '#')
    return ;
  parse.str(team.substr(1));
  parse >> nb;
  if (!(ss >> x >> y >> orient >> lvl >> team))
    return ;
  map.addPlayer(new t_player(nb, x, y, lvl, orient, team));
}

void Protocol::ppo(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::plv(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pin(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pex(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pbc(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pic(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pie(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pfk(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pdr(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pgt(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::pdi(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::enw(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::eht(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::ebo(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::edi(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::sgt(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::seg(const std::string &cmd, std::string &msg, Map &map)
{

}

void Protocol::smg(const std::string &cmd, std::string &, Map &)
{
  std::cout << cmd.substr(cmd.find(" ") + 1) << std::endl;
}

void Protocol::suc(const std::string &, std::string &, Map &)
{
  std::cerr << "Command Unknown" << std::endl;
}

void Protocol::sbp(const std::string &, std::string &, Map &)
{
  std::cerr << "Bad Command Argument" << std::endl;
}
