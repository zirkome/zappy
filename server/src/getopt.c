/*
** getopt.c<2> for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 11:11:11 2014 guillaume fillon
** Last update Sun May  4 17:07:26 2014 guillaume fillon
*/

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <err.h>

#include "server.h"

int	parse_option(int opt, t_world *option)
{
  if (opt == 'h')
    option->hflg = 1;
  if (opt == 'p')
    option->port = optarg;
  if (opt == 'x')
    option->width = stoi(optarg);
  if (opt == 'y')
    option->height = stoi(optarg);
  if (opt == 'v')
    {
      puts("Zappy server daemon v1.42");
      exit(EXIT_SUCCESS);
    }
  if (opt == '?')
    {
      option->unkflg = 1;
      return (-1);
    }
  return (0);
}
