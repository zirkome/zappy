/*
** string.h for string in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:51:02 2014 luc sinet
** Last update Mon Jun 30 10:38:41 2014 luc sinet
*/

#ifndef _STRINGS_H_
#define _STRINGS_H_

# define ALIGN(x, size) ((x + size - 1) &~ (size - 1))
# define ALLOC_SIZE 64
# define AV_MAP 8

typedef struct	s_string
{
  char		*content;
  int		size;
}		t_string;

void		string_init(t_string *string);
char		*string_append(t_string *string, char *app, int align_size);
int		string_erase(t_string *string, int type);

#endif /* _STRINGS_H_ */
