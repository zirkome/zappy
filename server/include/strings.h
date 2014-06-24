/*
** string.h for string in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:51:02 2014 luc sinet
** Last update Tue Jun 24 09:06:15 2014 luc sinet
*/

#ifndef _STRING_H_
# define _STRING_H_

typedef struct	s_string
{
  char		*content;
  int		size;
}		t_string;

void		string_init(t_string *string);
char		*string_append(t_string *string, char *app, int align_size);

#endif /* _STRING_H_ */
