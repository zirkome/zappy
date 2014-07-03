/*
** time.c for zappy in /home/kokaz/projects/tek2/unix/zappy/server
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Tue Jul  1 15:45:54 2014 guillaume fillon
** Last update Tue Jul  1 20:20:38 2014 guillaume fillon
*/

#include <time.h>

#include "scheduler.h"

time_t			clock_getsecond()
{
  struct timespec	ts;

  if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
    return ((time_t) -1);
  return (ts.tv_sec);
}

long			clock_getnanosecond()
{
  struct timespec	ts;

  if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
    return ((long) -1);
  return (ts.tv_nsec);
}
