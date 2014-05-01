#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <libsocket.h>

static int	g_sigint = 0;

static int	usage(FILE *stream)
{
  fputs("\nUsage:\n ./serveur PORT\n\n", stream);
  return ((stream == stderr) ? EXIT_FAILURE : EXIT_SUCCESS);
}

static void	handle_signal(int sig)
{
  if (sig == SIGINT)
    g_sigint = 1;
}

int		main(int argc, char *argv[])
{
  int	listenfd;

  if (argc != 2)
    return (usage(stderr));
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, &handle_signal);
  if ((listenfd = create_inet_server_socket(NULL, argv[1])) < 0)
    return (EXIT_FAILURE);
  while (!g_sigint)
    {
      pause();
    }
  close(listenfd);
  return (EXIT_SUCCESS);
}
