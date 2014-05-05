/*
** inet_socket.h for libsocket in /home/kokaz/projects/tek2/unix/PSU_2013_myirc
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Thu Apr 17 23:25:34 2014 guillaume fillon
** Last update Sat May  3 14:55:19 2014 Harold Fritsch
*/

#ifndef _INET_SOCKET_H_
# define _INET_SOCKET_H_

# include <netinet/in.h>

# define LIBSOCKET_BACKLOG 128

#ifdef __cplusplus
extern "C"
{
#endif
  int	create_inet_stream_socket(const char* host,
				  const char* service,
				  int flags);
  int	create_inet_server_socket(const char* host,
				  const char* service);
  
  int	socket_inet(int type, const char *proto);
  int	socket_inet2(int domain, int type, int protocol);
  
  int	bind_inet(int fd, const char *addr, in_port_t port);
  int	bind_inet2(int fd, const struct sockaddr *addr, socklen_t addrlen);
  
  int	connect_inet(int fd, const char *addr, in_port_t port);
  int	accept_inet(int fd, struct sockaddr_in *addr);
  
  ssize_t	write_socket_inet(int fd, char *buf, size_t size);
  ssize_t	read_socket_inet(int fd, char *buf, size_t size);
  ssize_t	receivefile(int out_fd, int in_fd);
#ifdef __cplusplus
}
#endif

#endif /* _INET_SOCKET_H_ */
