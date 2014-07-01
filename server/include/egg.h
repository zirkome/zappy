/*
** egg.h for egg in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jul  1 15:05:33 2014 luc sinet
** Last update Tue Jul  1 17:55:18 2014 luc sinet
*/

#ifndef _EGG_H_
# define _EGG_H_

# include <time.h>

typedef struct s_server	t_server;
typedef struct s_player	t_player;

typedef struct	s_egg
{
  int		x;
  int		y;
  time_t	remaining_time;
}		t_egg;

t_egg		*lay_egg(t_player *pl);
int		egg_hatching(t_server *server, t_egg *egg);

#endif /* _EGG_H_ */
