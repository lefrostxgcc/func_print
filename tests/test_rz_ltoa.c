#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../rz_numtostr.h"

START_TEST(test_min_long)
{
  char expected[128];
  long a = (long) 9223372036854775808UL;
  char *actual = rz_ltoa(a);
  snprintf(expected, sizeof expected, "%lld", a);
  ck_assert_pstr_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(test_max_long)
{
  char expected[128];
  long a = (long) 9223372036854775807UL;
  char *actual = rz_ltoa(a);
  snprintf(expected, sizeof expected, "%lld", a);
  ck_assert_pstr_eq(actual, expected);
  free(actual);
}
END_TEST

Suite *rz_ltoa_suite(void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("rz_ltoa");
  tc = tcase_create("rz_ltoa");
  tcase_add_test(tc, test_min_long);
  tcase_add_test(tc, test_max_long);
	
  suite_add_tcase(s, tc);

  return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *suite;
  SRunner *srunner;

  suite = rz_ltoa_suite();
  srunner = srunner_create(suite);
  srunner_run_all(srunner, CK_NORMAL);
  number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
