/*
** gui.h for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Fri Jul  4 14:50:48 2014 guillaume fillon
** Last update Wed Jul  9 23:02:49 2014 guillaume fillon
*/

#ifndef _GUI_H_
# define _GUI_H_

# include "server.h"

/*
** GUI client commands
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

/*
** GUI events callbacks
*/
typedef union	u_gui_arg
{
  int		id;
  char		*msg;
}		t_gui_arg;

typedef int (*t_gui_callback)(t_server *, t_client *, t_client *, t_gui_arg *);

int	gui_events_handling(t_server *server, t_client *client,
			    t_gui_arg *arg, t_gui_callback f);
int	gui_movements(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_player_connect(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_take(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_put(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_expulse(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_broadcast(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_incantation_start(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_incantation_end(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_fork_start(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_fork_end(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_egg_born(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_egg_dead(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_egg_connect(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_player_dead(t_server *, t_client *, t_client *, t_gui_arg *);
int	gui_team_win(t_server *, t_client *, t_client *, t_gui_arg *);

#endif /* _GUI_H_ */
