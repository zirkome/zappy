/*
** server.h for server in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 10:31:10 2014 luc sinet
** Last update Fri May  2 22:50:31 2014 luc sinet
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <libsocket.h>
# include "errors.h"

# define TIMEOUT (5 * 60)
# define UNUSED __attribute__((unused))
# define RSIZE 512

typedef struct	s_client t_client;

struct		s_client
{
  int		fd;
  t_ringb	*rb;
  t_client	*next;
};

typedef struct	s_serv
{
  int		fd;
  int		maxfd;
  fd_set	r_fd;
  fd_set	w_fd;
  t_client	*cl;
}		t_serv;

typedef struct	s_command
{
  char		*name;
  int		(*func)(void);
}		t_command;

int		init_serv(t_serv *serv, int ac, char **av);
void		init_fds(t_serv *serv);
void		handle_signal(int sig);
int		read_state(t_serv *serv);
int		write_state(t_serv *serv);
int		connect_new_user(t_serv *serv);
int		disconnect_user(t_serv *serv, t_client *cl);
int		add_user(t_client **cl, int fd);
int		pars_msg(t_serv *serv, t_client *cl, char *cmd);

#endif /* _SERVER_H_ */
