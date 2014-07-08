/*
** string.h for string in /home/sinet_l/Documents/project/zappy/server/src
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Mon Jun 23 10:51:02 2014 luc sinet
** Last update Mon Jul  7 21:40:06 2014 luc sinet
*/

#ifndef _STRINGS_H_
#define _STRINGS_H_

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# define ALIGN(x, size) ((x + size - 1) &~ (size - 1))
# define STRING_ALLOC_LIMIT 8192
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
int		string_size(t_string *string);
void		string_clear(t_string *string);
int		string_alloc_size(t_string *string);
void		string_shift(t_string *string, int pos);

#endif /* _STRINGS_H_ */
