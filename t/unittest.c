#include <stdlib.h>
#include <check.h>
#include <unistd.h>

#include "../src/zmpi.h"

#define check(x, msg) ck_assert_msg(x, msg)

START_TEST(mpi_finalize)
{
  check(MPI_Finalize() == MPI_SUCCESS,
	"MPI_Finalize valid arguments");
}
END_TEST

START_TEST(mpi_wtick)
{
  check(MPI_Wtick() == 0.000001,
	"mpi_wtick valid arguments");
}
END_TEST

START_TEST(mpi_get_processor_name)
{
  check(MPI_Get_processor_name(NULL, NULL) == MPI_ERR_ARG,
	"mpi_get_processor_name invalid arguments");

  int length = 128;
  char name[128];

  check(MPI_Get_processor_name(name, &length) == MPI_SUCCESS
	&& length > 0,
	"mpi_get_processor_name valid arguments");
}
END_TEST

START_TEST(mpi_get_version)
{
  check(MPI_Get_version(NULL, NULL) == MPI_ERR_ARG,
	"mpi_get_version invalid arguments");

  int version = -1;
  int subversion = -1;

  check(MPI_Get_version(&version, &subversion) == MPI_SUCCESS
	&& version == MPI_VERSION
	&& subversion == MPI_SUBVERSION,
	"mpi_get_version valid arguments");  
}
END_TEST

START_TEST(mpi_wtime)
{
  check(MPI_Wtime() > 0, "mpi_wtime positive double");
  
  double start = MPI_Wtime();
  usleep(100);

  check(MPI_Wtime() - start > 0, "mpi_wtime interval");
}
END_TEST

int main ()
{
  int failed = 0;

  Suite *s = suite_create("unittest");
  TCase *tc = tcase_create("unittest"); 

  tcase_add_test(tc, mpi_get_version);
  tcase_add_test(tc, mpi_wtime);
  tcase_add_test(tc, mpi_get_processor_name);
  tcase_add_test(tc, mpi_wtick);
  tcase_add_test(tc, mpi_finalize);

  suite_add_tcase(s, tc);

  SRunner *r = srunner_create(s);
  srunner_run_all(r, CK_NORMAL);
  failed = srunner_ntests_failed(r);
  srunner_free(r);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
