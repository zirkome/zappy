/*
** getopt.c<2> for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 11:11:11 2014 guillaume fillon
** Last update Thu Jun 26 15:46:12 2014 guillaume fillon
*/

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <err.h>

#include "server.h"

//TODO: Norme
int	parse_option(int opt, t_world *option, int argc, char *argv[])
{
  if (opt == 'h')
    option->hflg = 1;
  if (opt == 'c')
    option->slots = stoi(optarg);
  if (opt == 't')
    option->delay = stoi(optarg);
  if (opt == 'p')
    option->port = optarg;
  if (opt == 'x')
    option->width = stoi(optarg);
  if (opt == 'y')
    option->height = stoi(optarg);
  if (opt == 'n')
    {
      int index = optind - 1;

      while (index < argc)
	{
	  if (argv[index][0] != '-')
	    {
	      ++option->nb_teams;
	      option->teams =
		realloc(option->teams, option->nb_teams * sizeof(t_team));
	      if (option->teams == NULL)
		return (iperror("getopt: malloc", -1));
	      option->teams[option->nb_teams - 1].name = argv[index];
	    }
	  else
	    break;
	  index++;
	}
    }
  if (opt == 'v')
    {
      puts("Copyright (C) 2014 Guillaume Fillon, Luc Sinet\n\n" \
	   "Written by Guillaume Fillon and Luc Sinet.");
      exit(EXIT_SUCCESS);
    }
  if (opt == '?')
    {
      option->unkflg = 1;
      return (-1);
    }
  return (0);
}
