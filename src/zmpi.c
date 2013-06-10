#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <zmq.h>

#include "zmpi.h"

struct zmpi {
  void *context;
  void *sender;
  void *receiver;
  int enabled;
} zmpi;

int MPI_Send(void *buf, int count, MPI_Datatype datatype,
	     int dest, int tag, MPI_Comm comm)
{
  if (!buf || count < 0 || datatype < 0 || dest < 0 || tag < 0 || comm < 0)
    return MPI_ERR_ARG;

  return MPI_SUCCESS;
}

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

  *flag = !zmpi.enabled;

  return MPI_SUCCESS;
}

int MPI_Init_thread(int *argc, char ***argv, int required,
		    int *provided)
{
  if (!argc || !argv || !provided)
    return MPI_ERR_ARG;

  *provided = required;

  return MPI_Init(argc, argv);
}

int MPI_Init(int *argc, char ***argv)
{
  if (!argc || !argv)
    return MPI_ERR_ARG;

  void *context = zmq_ctx_new();
  if (!context)
    err(errno, "zmq_ctx_new");

  void *sender = zmq_socket(context, ZMQ_PUB);
  if (!sender)
    err(errno, "zmq_socket");

  void *receiver = zmq_socket(context, ZMQ_SUB);
  if (!receiver)
    err(errno, "zmq_socket");
  
  int ret = zmq_bind(sender, "epgm://eth0;239.192.1.1:5555");
  if (!ret)
    err(errno, "zmq_bind");

  ret = zmq_connect(receiver, "epgm://eth0;239.192.1.1:5555");
  if (!ret)
    err(errno, "zmq_connect");

  zmpi.context = context;
  zmpi.sender = sender;
  zmpi.receiver = receiver;
  zmpi.enabled = 1;

  return MPI_SUCCESS;
}

int MPI_Finalize(void)
{
  int ret;

  if (!zmpi.sender || !zmpi.receiver || !zmpi.context)
    return MPI_ERR_SERVICE;

  ret = zmq_close(zmpi.sender);
  if (ret)
    err(errno, "zmq_close");

  ret = zmq_close(zmpi.receiver);
  if (ret)
    err(errno, "zmq_close");

  ret = zmq_ctx_destroy(zmpi.context);
  if (ret)
    err(errno, "zmq_ctx_destroy");

  zmpi.enabled = 0;

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
