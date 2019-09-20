#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ft_printf.h"
#include "rz_write.h"

void setup_ft_printf(void)
{
  free_write_buf();
}

void teardown_ft_printf(void)
{
  free_write_buf();
}

START_TEST(test_single_format_param)
{
  int result;

  result = ft_printf("Hello");
  ck_assert_int_eq(result, 5);
  ck_assert_pstr_eq(get_write_buf(), "Hello");
}
END_TEST

START_TEST(test_single_format_param_null)
{
  int result;

  result = ft_printf(NULL);
  ck_assert_int_eq(result, -1);
  ck_assert_pstr_eq(get_write_buf(), NULL);
}
END_TEST

START_TEST(test_single_format_param_empty)
{
  int result;

  result = ft_printf("");
  ck_assert_int_eq(result, 0);
  ck_assert_pstr_eq(get_write_buf(), NULL);
}
END_TEST

START_TEST(test_single_param_char)
{
  int result;

  result = ft_printf("%c", 'a');
  ck_assert_int_eq(result, 1);
  ck_assert_pstr_eq(get_write_buf(), "a");
}
END_TEST

START_TEST(test_single_param_cstring)
{
  int result;

  result = ft_printf("%s", "C string");
  ck_assert_int_eq(result, 8);
  ck_assert_pstr_eq(get_write_buf(), "C string");
}
END_TEST

START_TEST(test_single_param_cstring_empty)
{
  int result;

  result = ft_printf("%s", "");
  ck_assert_int_eq(result, 0);
  ck_assert_pstr_eq(get_write_buf(), NULL);
}
END_TEST

START_TEST(test_single_format_param_percent)
{
  int result;

  result = ft_printf("%%");
  ck_assert_int_eq(result, 1);
  ck_assert_pstr_eq(get_write_buf(), "%");
}
END_TEST

START_TEST(test_single_param_d)
{
  char buffer[64];
  int a = 12345;
  int actual_result = ft_printf("%d", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%d", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_i)
{
  char buffer[64];
  int a = 987;
  int actual_result = ft_printf("%i", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%i", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_min_int)
{
  char buffer[128];
  int a = -2147483648;
  int actual_result = ft_printf("%d", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%d", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_max_int)
{
  char buffer[128];
  int a = 2147483647;
  int actual_result = ft_printf("%d", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%d", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_zero)
{
  char buffer[128];
  int a = 0;
  int actual_result = ft_printf("%d", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%d", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

Suite *ft_printf_suite(void)
{
  Suite *s;
  TCase *tc_single_format_param;
  TCase *tc_single_param;

  s = suite_create("ft_printf");
  tc_single_format_param = tcase_create("Single format param");
  tcase_add_checked_fixture(tc_single_format_param, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_single_format_param, test_single_format_param);
  tcase_add_test(tc_single_format_param, test_single_format_param_null);
  tcase_add_test(tc_single_format_param, test_single_format_param_empty);
  tcase_add_test(tc_single_format_param, test_single_format_param_percent);

  tc_single_param = tcase_create("Single param");
  tcase_add_checked_fixture(tc_single_param, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_single_param, test_single_param_char);
  tcase_add_test(tc_single_param, test_single_param_cstring);
  tcase_add_test(tc_single_param, test_single_param_cstring_empty);
  tcase_add_test(tc_single_param, test_single_param_d);
  tcase_add_test(tc_single_param, test_single_param_i);

  tcase_add_test(tc_single_param, test_single_param_min_int);
  tcase_add_test(tc_single_param, test_single_param_max_int);
  tcase_add_test(tc_single_param, test_single_param_zero);
	
  suite_add_tcase(s, tc_single_format_param);
  suite_add_tcase(s, tc_single_param);

  return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *suite;
  SRunner *srunner;

  suite = ft_printf_suite();
  srunner = srunner_create(suite);
  srunner_run_all(srunner, CK_NORMAL);
  number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
