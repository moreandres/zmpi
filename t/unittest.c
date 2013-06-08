#include <stdlib.h>
#include <check.h>

#include "../src/zmpi.h"

START_TEST(test)
{
  ;
}
END_TEST

int main ()
{
  int failed = 0;

  Suite *s = suite_create("unittest");
  TCase *tc = tcase_create("unittest");
  
  tcase_add_test(tc, test);
  suite_add_tcase(s, tc);

  SRunner *r = srunner_create(s);
  srunner_run_all(r, CK_NORMAL);
  failed = srunner_ntests_failed(r);
  srunner_free(r);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
