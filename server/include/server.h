
/*
** server.h for server in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 10:31:10 2014 luc sinet
** Last update Fri Jun 20 17:33:23 2014 luc sinet
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# include <sys/epoll.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <libsocket.h>

# include "errors.h"

#ifndef MAX_EPOLL_EVENTS
# define MAX_EPOLL_EVENTS 128
#endif

# define DEFAULT_PORT "6000"
# define TIMEOUT (5 * 60)
# define UNUSED __attribute__((unused))
# define RSIZE 512
# define DISCONNECTED 2
# define CMDLEN 32
# define ARGLEN 256

enum	e_command
  {
    FORWARD = 1,
    RIGHT = 2,
    LEFT = 3,
    SEE = 4,
    INVENTORY = 5,
    TAKE = 6,
    PUT = 7,
    EXPULSE = 8,
    BROADCAST = 9,
    INCANTATION = 10,
    FORK = 11,
    CONNECT_NBR = 12,
    MSZ = 13,
    BCT = 14,
    MCT = 15,
    TNA = 16,
    PPO = 17,
    PLV = 18,
    PIN = 19,
    SGT = 20,
    SST = 21
  };

typedef enum	bool
  {
    false = 0,
    true
  }		t_bool;

typedef enum	etype
  {
    string = 0,
    number,
    none
  }		t_type;

typedef enum	edir
  {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
  }		t_dir;

typedef struct	s_player
{
  int		x;
  int		y;
  t_dir		dir;
}		t_player;

typedef struct	s_client t_client;

struct		s_client
{
  int		fd;
  t_ringb	*rb;
  t_queue	*queue;
  char		*teamptr;
  t_player	*player;
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

typedef struct		s_server
{
  int			fd;
  struct epoll_event	events[MAX_EPOLL_EVENTS];
  t_world		world;
  t_client		*cl;
}			t_server;

typedef struct	s_command
{
  char		*name;
  t_bool       	arg;
  t_type	type;
  int		(*func)(t_server *server, t_client *client, char *arg);
}		t_command;

int		parse_option(int opt, t_world *option);
long		stoi(char *str);

int		init_server(t_server *server);
void		init_fds(t_server *server);
int		read_state(t_server *server, t_client *client);
int		write_state(t_server *server, t_client *client);
int		connect_new_user(t_server *server);
int		disconnect_user(t_server *server, t_client *cl);
int		add_user(t_client **cl, int fd);

int		process_input(t_server *server, t_client *cl, char *input);
t_bool		check_argument_type(char *arg, t_command *cmds, int idx);

void		welcome_server(char *port);

/*
** epoll/monitoring
*/
int		start_monitoring(t_server *server);
int		epoll_create_monitor();
int		epoll_monitor(struct epoll_event events[],
			      int maxevents, int timeout);
int		epoll_event_add(int fd, struct epoll_event *ev);
int		epoll_event_mod(int fd, struct epoll_event *ev);
int		epoll_event_del(int fd, struct epoll_event *ev);

/*
** Player commands
*/

int		pl_forward(t_server *server, t_client *client, char *arg);
int		pl_right(t_server *server, t_client *client, char *arg);
int		pl_left(t_server *server, t_client *client, char *arg);
int		pl_see(t_server *server, t_client *client, char *arg);
int		pl_take(t_server *server, t_client *client, char *arg);
int		pl_put(t_server *server, t_client *client, char *arg);
int		pl_expulse(t_server *server, t_client *client, char *arg);
int		pl_broadcast(t_server *server, t_client *client, char *arg);
int		pl_inventory(t_server *server, t_client *client, char *arg);
int		pl_incantation(t_server *server, t_client *client, char *arg);
int		pl_fork(t_server *server, t_client *client, char *arg);
int		pl_connect_nbr(t_server *server, t_client *client, char *arg);

#endif /* _SERVER_H_ */
