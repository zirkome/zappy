#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <libsocket.h>
#include "LaunchGfx.hpp"

static int	usage(FILE *stream)
{
  fputs("\nUsage:\n ./client IP PORT\n\n", stream);
  return ((stream == stderr) ? EXIT_FAILURE : EXIT_SUCCESS);
}

int		main(int argc, char *argv[])
{
  char	*ip = NULL;
  char	*port = NULL;
  char	*team_name = NULL;
  int	listenfd;
  int	opt;

  signal(SIGPIPE, SIG_IGN);
  while ((opt = getopt(argc, argv, "n:h:p:")) != -1)
    {
      switch (opt)
	{
	case 'n':
	  team_name = argv[optind - 1];
	  break;
	case 'h':
	  ip = argv[optind - 1];
	  break;
	case 'p':
	  port = argv[optind - 1];
	  break;
	default:
	  return (usage(stderr));
	}
    }
  printf("team_name : %s\nip : %s\nport : %s\n", team_name, ip, port);
  if ((listenfd = create_inet_stream_socket(ip, port, 0)) < 0)
    return (EXIT_FAILURE);
  close(listenfd);
  return (EXIT_SUCCESS);
}
