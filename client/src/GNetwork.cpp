#include "GNetwork.hpp"

GNetwork::GNetwork(): _fd(-1)
{

}

GNetwork::~GNetwork()
{

}

bool GNetwork::open(const std::string &ip, const std::string &port)
{
  if (_fd != -1)
    close();
  if ((_fd = create_inet_stream_socket(ip.c_str(), port.c_str(), 0)) < 0)
    return (false);
  return (true);
}

bool GNetwork::close()
{
  if (_fd == -1 || ::close(_fd) == -1)
    return (false);
  return (true);
}

void GNetwork::update(/* Map &map */)
{
  // char buf[512];
  // char aligned[_buffer.size + 1];
  // char *tmp;
  // ssize_t retv;
  // fd_set rds;

  // FD_ZERO(&rds);
  // FD_SET(_fd, &rds);

  // if (select(_fd + 1, &rds, NULL, NULL, NULL) == -1)
  //   return ;
  // if (FD_ISSET(_fd, &rds))
  //   {
  //     tmp = aligned;
  //     if ((retv = read(_fd, buf, 512)) <= 0)
  // 	throw(Exception("Server disconnected"));
  //     fill_ringbuffer(&_buffer, buf, retv);
  //     align_ringbuffer(&_buffer, aligned, sizeof(aligned));
  //     while ((retv = get_char_pos(&_buffer, tmp, '\n')) != -1)
  // 	{
  // 	  tmp[retv] = '\0';
  // 	  std::cout << "Cmd => " << tmp << std::endl;
  // 	  tmp = &tmp[retv + 1];
  // 	}
  //   }
}
