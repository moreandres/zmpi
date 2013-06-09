#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>

#include "zmpi.h"

int MPI_Get_processor_name(char *name, int *length)
{
  if (!name || !length)
    return MPI_ERR_ARG;

  int ret = gethostname(name, *length);

  return MPI_SUCCESS;
}

int MPI_Get_version(int *version, int *subversion)
{
  if (!version || !subversion)
    return MPI_ERR_ARG;

  *version = MPI_VERSION;
  *subversion = MPI_SUBVERSION;

  return MPI_SUCCESS;
}

double MPI_Wtime(void)
{
  double sec;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  sec = tv.tv_sec + tv.tv_usec / 1000000.0;
  return sec;
}

int main(int argc, char *argv[])
{
  return EXIT_SUCCESS;
}
