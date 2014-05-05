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
  int	listenfd;

  launchGfx();
  if (argc != 3)
    return (usage(stderr));
  signal(SIGPIPE, SIG_IGN);
  if ((listenfd = create_inet_stream_socket(argv[1], argv[2], 0)) < 0)
    return (EXIT_FAILURE);
  close(listenfd);
  return (EXIT_SUCCESS);
}
