/*
** server.h for server in /home/sinet_l/Documents/project/PSU_2013_myirc/src/fserver
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Thu Apr 17 10:31:10 2014 luc sinet
** Last update Wed Jul  2 22:39:32 2014 guillaume fillon
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# include <sys/epoll.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <stdarg.h>
# include <libsocket.h>

# include "generic_list.h"
# include "enums.h"
# include "errors.h"
# include "strings.h"
# include "vectors.h"
# include "geometry.h"

#ifndef MAX_EPOLL_EVENTS
# define MAX_EPOLL_EVENTS 128
#endif

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define MAP_POS(x, y, width) (y * width + x)

# define DEFAULT_PORT "6000"
# define TIMEOUT (5 * 60)
# define UNUSED __attribute__((unused))
# define RSIZE 512
# define DISCONNECTED 2

# define CMDLEN 32
# define ARGLEN 256

# define CASE_PROB 5
# define ITEM_PROB THYSTAME
# define NB_ELEM (EMPTY - 1)

typedef enum	e_arg_type
  {
    string = 0,
    number,
    none
  }		t_arg_type;

typedef enum	e_client_type
  {
    GRAPHIC,
    IA,
    EGG,
    UNKNOWN
  }		t_client_type;

typedef enum	e_dir
  {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
  }		t_dir;

typedef struct	s_team
{
  char		*name;
  int		slots;
}		t_team;

typedef struct	s_player
{
  int		id;
  int		x;
  int		y;
  t_dir		dir;
  int		level;
  int		inventory[NB_ELEM];
  t_list	jobs;
  t_team	*teamptr;
}		t_player;

typedef struct	s_client
{
  int		fd;
  t_client_type	type;
  t_bool	ghost;
  t_ringb	*rb;
  t_queue	*queue;
  t_player	*player;
}		t_client;

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
  time_t	delay;
  int		nb_teams;
  t_team	*teams;
  int		hflg;
  int		unkflg;
}		t_world;

typedef struct		s_server
{
  int			fd;
  struct epoll_event	events[MAX_EPOLL_EVENTS];
  t_world		world;
  t_list		cl;
}			t_server;

typedef int (*t_callback)(t_server *, t_client *, char *);

typedef struct	s_command
{
  char		*name;
  t_bool       	arg;
  t_arg_type	type;
  t_callback	func;
  time_t	delay;
}		t_command;

/*
** Util
*/
long		stoi(char *str);
__attribute__((format (printf, 2, 3)))
char		*cnprintf(size_t size, const char *format, ...);
char		*vcnprintf(size_t size, const char *format, va_list ap);

int		parse_option(int opt, t_world *option, int argc, char *argv[]);

int		init_server(t_server *server);
void		init_fds(t_server *server);
int		generate_map(t_world *world);
char		*get_element_name(t_world *world, int x, int y,
				  unsigned int pos);
int		get_element_id(char *name);
char		*get_name_from_id(int id);
int		add_to_world(t_world *world, int type, int x, int y);
int		remove_from_world(t_world *world, int type, int x, int y);
t_client       	*get_client_by_pos(t_client *cl, t_world *world,
				   int x, int y);
void		apply_map_looping(int *x, int *y, int wdx, int wdy);
int		count_type_on_box(t_world *world, int type, int x, int y);
int		count_player_in_team(t_list cl, t_team *team);

int		read_state(t_server *server, t_client *client);
int		write_state(t_server *server, t_client *client);
int		connect_new_user(t_server *server);
int		kick_user(t_list *list, t_client *cl, t_world *world);
int		disconnect_user(t_server *server, t_client *cl);

/*
** Client
*/
t_client	*client_new(int fd);

int		process_input(t_server *server, t_client *cl, char *input);
t_bool		check_argument_type(char *arg, t_command *cmd);

void		welcome_server(char *port);

int		add_to_inventory(t_player *player, int type, int amount);
int		remove_from_inventory(t_player *player, int type, int amount);

void		translate_point(t_geometry *geo, t_world *world, int dist);
int		find_case(t_geometry *geo, double *x, double *y);
int		get_case_pos(double ax, double ay,
			     double x, double y);

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
** Authentication
*/
int		authenticate_user(t_server *server, t_client *cl, char *input);

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
int		pl_lay_egg(t_server *server, t_client *client, char *arg);
int		pl_fork(t_server *server, t_client *client, char *arg);
int		pl_connect_nbr(t_server *server, t_client *client, char *arg);

/*
** GUI commands
*/
int		gui_welcome(t_server *server, t_client *client);
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
