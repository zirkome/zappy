/*
** main.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 16:42:29 2014 guillaume fillon
** Last update Thu Jun 19 16:41:26 2014 guillaume fillon
*/

#include <signal.h>
#include <getopt.h>
#include <locale.h>

#include "server.h"

static int	g_sigint = 0;

static struct option	g_longopts[] =
  {
    {"port", required_argument, NULL, 'p'},
    {"width", required_argument, NULL, 'x'},
    {"height", required_argument, NULL, 'y'},
    {"client", required_argument, NULL, 'c'},
    {"timing", required_argument, NULL, 't'},
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}
  };

static void	usage(FILE *output)
{
  fputs("\nUsage:\n"
	" zappyd [options]\n"
	"Options:\n"
	" -p, --port <port>       run the server on this port\n"
	" -x, --width <size>      set the width of the map\n"
	" -y, --height <size>     set the height of the map\n"
	" -c, --client <max>      number of allowed clients per team\n"
	" -t, --timing <delay>    time delay of the actions\n"
	" -v, --version           output version information and exit\n"
	" -h, --help              display this help and exit\n\n", output);
  exit(output == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void	handle_signal(int sig)
{
  if (sig == SIGINT)
    g_sigint = 1;
}

int		main(int argc, char *argv[])
{
  t_server	server;
  int		opt;
  int		opt_index;

  setlocale(LC_ALL, "");
  setlocale(LC_NUMERIC, "C");
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR ||
      signal(SIGINT, &handle_signal) == SIG_ERR)
    return (iperror("signal", -1));
  memset(&server.world, 0, sizeof(server.world));
  opt_index = 0;
  while ((opt = getopt_long(argc, argv, "p:x:y:c:t:vh",
			    g_longopts, &opt_index)) != -1)
    if (parse_option(opt, &server.world) != 0)
      break;
  if (server.world.hflg || server.world.unkflg)
    usage(server.world.hflg ? stdout : stderr);
  if (init_server(&server) == -1)
    return (-1);
  start_monitoring(&server);
  close(server.fd);
  return (EXIT_SUCCESS);
}
