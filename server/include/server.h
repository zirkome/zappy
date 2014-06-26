/*
** server.h for server in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 10:31:10 2014 luc sinet
** Last update Thu Jun 26 20:41:20 2014 luc sinet
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# include <sys/epoll.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <libsocket.h>

# include "enums.h"
# include "errors.h"
# include "strings.h"

#ifndef MAX_EPOLL_EVENTS
# define MAX_EPOLL_EVENTS 128
#endif

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define MAP_POS(x, y, width) (y + width + x)
# define ALIGN(x, size) ((x + size - 1) &~ (size - 1))
# define ALLOC_SIZE 64
# define AV_MAP 8

# define DEFAULT_PORT "6000"
# define TIMEOUT (5 * 60)
# define UNUSED __attribute__((unused))
# define RSIZE 512
# define DISCONNECTED 2

# define CMDLEN 32
# define ARGLEN 256

# define CASE_PROB 5
# define ITEM_PROB 6
# define NB_ELEM 7

typedef enum	bool
  {
    false = 0,
    true
  }		t_bool;

typedef enum	e_arg_type
  {
    string = 0,
    number,
    none
  }		t_arg_type;

typedef enum	e_client_type
  {
    GRAPHIC,
    IA
  }		t_client_type;

typedef enum	e_dir
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
  int		level;
}		t_player;

typedef struct	s_client t_client;

struct		s_client
{
  int		fd;
  t_client_type	type;
  t_ringb	*rb;
  t_queue	*queue;
  char		*teamptr;
  t_player	*player;
  t_client	*next;
};

/**
 * @port TCP port of the server (-p)
 * @width Width of the map (-x)
 * @height Height of the map (-y)
 * @slots Number of clients allowed at the game beginning (-c)
 * @delay Time delay for executing actions (-t)
 * @teams Name of the world's teams (-n)
 * @hflg Help flag (-h)
 * @unkflg Unknown flag (-?)
 */
typedef struct	s_world
{
  char		*port;
  int		width;
  int		height;
  t_string	**map;
  int		slots;
  int		delay;
  int		nb_teams;
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
  t_arg_type	type;
  int		(*func)(t_server *server, t_client *client, char *arg);
}		t_command;

int		parse_option(int opt, t_world *option, int argc, char *argv[]);
long		stoi(char *str);

int		init_server(t_server *server);
void		init_fds(t_server *server);
int		generate_map(t_world *world);
char		*get_element_name(t_world *world, int x, int y,
				  unsigned int pos);

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

/*
** GUI commands
*/
int		gui_msz(t_server *server, t_client *client, char *arg);
int		gui_bct(t_server *server, t_client *client, char *arg);
int		gui_mct(t_server *server, t_client *client, char *arg);
int		gui_tna(t_server *server, t_client *client, char *arg);
int		gui_ppo(t_server *server, t_client *client, char *arg);
int		gui_plv(t_server *server, t_client *client, char *arg);
int		gui_pin(t_server *server, t_client *client, char *arg);
int		gui_sgt(t_server *server, t_client *client, char *arg);
int		gui_sst(t_server *server, t_client *client, char *arg);

#endif /* _SERVER_H_ */
