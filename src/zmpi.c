#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "zmpi.h"

int MPI_Comm_rank(MPI_Comm comm, int *rank)
{
  if (comm > 0 || !rank)
    return MPI_ERR_ARG;

  *rank = comm;

  return MPI_SUCCESS;
}

int MPI_Comm_size(MPI_Comm comm, int *size)
{
  if (comm > 0 || !size)
    return MPI_ERR_ARG;

  *size = comm;

  return MPI_SUCCESS;
}

int MPI_Finalized(int *flag)
{
  if (!flag)
    return MPI_ERR_ARG;

  *flag = 1;

  return MPI_SUCCESS;
}

int MPI_Init_thread(int *argc, char ***argv, int required,
		    int *provided)
{
  if (!argc || !argv || !provided)
    return MPI_ERR_ARG;

  *provided = required;

  return MPI_SUCCESS;
}

int MPI_Init(int *argc, char ***argv)
{
  if (!argc || !argv)
    return MPI_ERR_ARG;

  return MPI_SUCCESS;
}

int MPI_Finalize(void)
{
  return MPI_SUCCESS;
}

double MPI_Wtick(void)
{
  return MPI_WTICK;
}

int MPI_Get_processor_name(char *name, int *length)
{
  if (!name || !length)
    return MPI_ERR_ARG;

  int ret = gethostname(name, *length);
  if (ret)
    return MPI_ERR_ACCESS;

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
  if (argc < 0 || !argv)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
