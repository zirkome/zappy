/*
** server.h for server in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 10:31:10 2014 luc sinet
** Last update Wed Jun 18 14:08:09 2014 luc sinet
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <libsocket.h>

# include "errors.h"

# define DEFAULT_PORT "6000"
# define TIMEOUT (5 * 60)
# define UNUSED __attribute__((unused))
# define RSIZE 512
# define DISCONNECTED 2
# define CMDLEN 32
# define ARGLEN 256

typedef enum	ebool
  {
    false = 0,
    true
  }		bool;

typedef struct	s_client t_client;

struct		s_client
{
  int		fd;
  t_ringb	*rb;
  t_queue	*queue;
  char		*teamptr;
  t_client	*next;
};

typedef struct	s_world
{
  char		*port;
  int		width;
  int		height;
  int		max_allowed;
  int		delay;
  char		**teams;
  int		hflg;
  int		unkflg;
}		t_world;

typedef struct	s_server
{
  int		fd;
  int		maxfd;
  fd_set	r_fd;
  fd_set	w_fd;
  t_client	*cl;
  t_world	world;
}		t_server;

typedef struct	s_command
{
  char		*name;
  bool		arg;
  int		(*func)(char *arg);
}		t_command;

int		parse_option(int opt, t_world *option);
long		stoi(char *str);

int		init_server(t_server *server);
void		init_fds(t_server *server);
int		read_state(t_server *server);
int		write_state(t_server *server);
int		connect_new_user(t_server *server);
int		disconnect_user(t_server *server, t_client *cl);
int		add_user(t_client **cl, int fd);
int		process_input(t_server *server, t_client *cl, char *input);
void		welcome_server(char *port);

#endif /* _SERVER_H_ */
