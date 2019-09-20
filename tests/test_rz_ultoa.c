#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../rz_numtostr.h"

START_TEST(test_zero)
{
  char expected[128];
  unsigned long a = 0;
  char *actual = rz_ultoa(a);
  snprintf(expected, sizeof expected, "%lu", a);
  ck_assert_pstr_eq(actual, expected);
  free(actual);
}
END_TEST

Suite *rz_ultoa_suite(void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("rz_ultoa");
  tc = tcase_create("rz_ultoa");
  tcase_add_test(tc, test_zero);
	
  suite_add_tcase(s, tc);

  return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *suite;
  SRunner *srunner;

  suite = rz_ultoa_suite();
  srunner = srunner_create(suite);
  srunner_run_all(srunner, CK_NORMAL);
  number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
