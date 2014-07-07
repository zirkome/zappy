#include "GameEngine.hpp"
#include "GNetwork.hpp"

GNetwork::GNetwork(): _fd(-1), _proto()
{
  if ((_buffer = create_ringbuffer(1024)) == NULL)
    throw(Exception("Cannot create the ring buffer"));
}

GNetwork::~GNetwork()
{
  delete _buffer;
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

void GNetwork::update(t_display &map)
{
  char buf[512];
  char aligned[_buffer->size + 1];
  char *tmp;
  ssize_t retv;
  fd_set rds;
  fd_set wrs;
  std::string msg;
  struct timeval time;

  FD_ZERO(&rds);
  FD_ZERO(&wrs);
  FD_SET(_fd, &rds);
  FD_SET(_fd, &wrs);
  time.tv_sec = 0;
  time.tv_usec = 1000;

  if (select(_fd + 1, &rds, &wrs, NULL, &time) == -1)
    return ;
  if (FD_ISSET(_fd, &rds))
    {
      tmp = aligned;
      if ((retv = read_socket_inet(_fd, buf, 512)) <= 0)
	throw(Exception("Connection Lost"));
      fill_ringbuffer(_buffer, buf, retv);
      align_ringbuffer(_buffer, aligned, sizeof(aligned));
      while ((retv = get_char_pos(_buffer, tmp, '\n')) != -1)
	{
	  tmp[retv] = '\0';
	  msg = _proto.parseCmd(std::string(tmp), map);
	  if (!msg.empty())
	    _msg.push(msg);
	  tmp = &tmp[retv + 1];
	}
    }
  else if (FD_ISSET(_fd, &wrs))
    while (!_msg.empty())
      {
	send(_msg.front());
	_msg.pop();
      }
}

void GNetwork::send(const std::string &msg)
{
  int tmp;
  for (unsigned int i = 0;i < msg.size() &&
	 (tmp = write(_fd, &(msg.c_str())[i], msg.size() - i)) > 0;i += tmp);
  if (tmp <= 0)
    throw(Exception("Connection Lost"));
}

void GNetwork::changeTime(int t)
{
  _msg.push(_proto.changeTime(t));
}
