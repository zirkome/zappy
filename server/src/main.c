/*
** main.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun May  4 16:42:29 2014 guillaume fillon
** Last update Sun May  4 17:19:49 2014 guillaume fillon
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

static int	monitor_fd(t_serv *serv)
{
  init_fds(serv);
  if (select(serv->maxfd + 1, &serv->r_fd, &serv->w_fd,
	     NULL, NULL) == -1)
    return (iperror("accept_connection: select", -1));
  read_state(serv);
  write_state(serv);
  return (0);
}

int		main(int argc, char *argv[])
{
  t_serv	serv;
  int		opt;
  int		opt_index;

  setlocale(LC_ALL, "");
  setlocale(LC_NUMERIC, "C");
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR ||
      signal(SIGINT, &handle_signal) == SIG_ERR)
    return (iperror("init_serv: signal", -1));
  memset(&serv.world, 0, sizeof(serv.world));
  opt_index = 0;
  while ((opt = getopt_long(argc, argv, "p:x:y:c:t:vh",
			    g_longopts, &opt_index)) != -1)
    if (parse_option(opt, &serv.world) != 0)
      break;
  if (serv.world.hflg || serv.world.unkflg)
    usage(serv.world.hflg ? stdout : stderr);
  if (init_serv(&serv) == -1)
    return (-1);
  while (!g_sigint)
    monitor_fd(&serv);
  close(serv.fd);
  return (EXIT_SUCCESS);
}
