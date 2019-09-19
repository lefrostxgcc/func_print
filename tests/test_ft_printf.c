#include <check.h>
#include <stdlib.h>
#include "../ft_printf.h"
#include "rz_write.h"

void setup_ft_printf(void)
{
}

void teardown_ft_printf(void)
{
}

START_TEST(test_single_format_param)
{
	int result;

	result = ft_printf("Hello");
	ck_assert_int_eq(result, 5);
	ck_assert_pstr_eq(get_write_buf(), "Hello");
	free_write_buf();
}
END_TEST

START_TEST(test_single_format_param_null)
{
	int result;

	free_write_buf();
	result = ft_printf(NULL);
	ck_assert_int_eq(result, -1);
	ck_assert_pstr_eq(get_write_buf(), NULL);
	free_write_buf();
}
END_TEST

Suite *ft_printf_suite(void)
{
	Suite *s;
	TCase *tc_single_format_param;

	s = suite_create("ft_printf");
	tc_single_format_param = tcase_create("Single format param");
	tcase_add_checked_fixture(tc_single_format_param, setup_ft_printf, teardown_ft_printf);
	tcase_add_test(tc_single_format_param, test_single_format_param);
	tcase_add_test(tc_single_format_param, test_single_format_param_null);
	
	suite_add_tcase(s, tc_single_format_param);

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
