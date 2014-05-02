/*
** error.h for error in /home/sinet_l/Documents/project/PSU_2013_myftp
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Sun Apr  6 10:44:42 2014 luc sinet
** Last update Fri May  2 09:51:09 2014 luc sinet
*/

#ifndef _ERROR_H_
# define _ERROR_H_

int	ierror(const char *s, int ret);
void	*pterror(const char *s, void *ret);
int	iperror(const char *func, int ret);
void	*ptperror(const char *func, void *ret);

#endif /* _ERROR_H_ */
