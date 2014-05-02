#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "server.h"

static int	g_sigint = 0;

static int	usage(FILE *stream)
{
  fputs("\nUsage:\n ./serveur PORT\n\n", stream);
  return ((stream == stderr) ? EXIT_FAILURE : EXIT_SUCCESS);
}

void	handle_signal(int sig)
{
  if (sig == SIGINT)
    g_sigint = 1;
}

int	monitor_fd(t_serv *serv)
{
  (void)serv;
  return (0);
}

int		main(int ac, char **av)
{
  t_serv	serv;

  if (ac != 2)
    return (usage(stderr));
  if (init_serv(&serv, ac, av) == -1)
    return (-1);
  while (!g_sigint)
    monitor_fd(&serv);
  close(serv.fd);
  return (EXIT_SUCCESS);
}
