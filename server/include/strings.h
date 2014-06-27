/*
** string.h for string in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:51:02 2014 luc sinet
** Last update Fri Jun 27 23:28:25 2014 guillaume fillon
*/

#ifndef _STRINGS_H_
#define _STRINGS_H_

typedef struct	s_string
{
  char		*content;
  int		size;
}		t_string;

void		string_init(t_string *string);
char		*string_append(t_string *string, char *app, int align_size);
int		string_erase(t_string *string, int type);

#endif /* _STRINGS_H_ */
