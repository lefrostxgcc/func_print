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
  char buffer[128];
  const char *format = "Hello";
  int actual_result = ft_printf(format);
  int expected_result = snprintf(buffer, sizeof buffer, format);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_format_param_null)
{
  char buffer[128] = "abcde";
  const char *format = NULL;
  int actual_result = ft_printf(format);
  ck_assert_int_eq(actual_result, -1);
  ck_assert_pstr_eq(get_write_buf(), NULL);
}
END_TEST

START_TEST(test_single_format_param_empty)
{
  char buffer[128] = "12345";
  const char *format = "";
  int actual_result = ft_printf(format);
  ck_assert_int_eq(actual_result, 0);
  ck_assert_pstr_eq(get_write_buf(), NULL);
}
END_TEST

START_TEST(test_single_param_char)
{
  char buffer[128];
  const char *format = "%c";
  int a = 'a';
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_cstring)
{
  char buffer[128];
  const char *format = "%s";
  const char *a = "C string";
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_single_param_cstring_empty)
{
  char buffer[128];
  const char *format = "%s";
  const char *a = "";
  int actual_result = ft_printf(format, a);
  ck_assert_int_eq(actual_result, 0);
  ck_assert_pstr_eq(get_write_buf(), NULL);
}
END_TEST

START_TEST(test_single_format_param_percent)
{
  char buffer[128];
  const char *format = "%%";
  int actual_result = ft_printf(format);
  int expected_result = snprintf(buffer, sizeof buffer, format);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
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

START_TEST(test_single_param_min_uint)
{
  char buffer[128];
  int a = 0;
  int actual_result = ft_printf("%u", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%u", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_max_uint)
{
  char buffer[128];
  unsigned int a = 4294967295;
  int actual_result = ft_printf("%u", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%u", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hhd)
{
  char buffer[128];
  int a = 123;
  int actual_result = ft_printf("%hhd", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hhd", a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_single_param_hhi)
{
  char buffer[128];
  int a = 97;
  int actual_result = ft_printf("%hhi", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hhi", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hhu)
{
  char buffer[128];
  unsigned int a = 157;
  int actual_result = ft_printf("%hhu", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hhu", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hd)
{
  char buffer[128];
  short a = -23456;
  int actual_result = ft_printf("%hd", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hd", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hi)
{
  char buffer[128];
  short a = 13579;
  int actual_result = ft_printf("%hi", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hi", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hu)
{
  char buffer[128];
  unsigned short a = 51234;
  int actual_result = ft_printf("%hu", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hu", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_ld)
{
  char buffer[128];
  long a = -3000000000;
  int actual_result = ft_printf("%ld", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%ld", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_li)
{
  char buffer[128];
  long a = 4000000000;
  int actual_result = ft_printf("%li", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%li", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_lu)
{
  char buffer[128];
  unsigned long a = (1UL << 63) + (1UL << 16);
  int actual_result = ft_printf("%lu", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%lu", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_lld)
{
  char buffer[128];
  long a = -89000000000;
  int actual_result = ft_printf("%lld", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%lld", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_lli)
{
  char buffer[128];
  long a = 5679000000000;
  int actual_result = ft_printf("%lli", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%lli", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_llu)
{
  char buffer[128];
  unsigned long a = (1UL << 63) + (1UL << 16) + (1 << 20);
  int actual_result = ft_printf("%llu", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%llu", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_o)
{
  char buffer[128];
  unsigned long a = 123456789;
  int actual_result = ft_printf("%o", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%o", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hho)
{
  char buffer[128];
  int a = -130;
  int actual_result = ft_printf("%hho", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hho", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_ho)
{
  char buffer[128];
  int a = 567891234;
  int actual_result = ft_printf("%ho", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%ho", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_lo)
{
  char buffer[128];
  long a = (1L << 40);
  int actual_result = ft_printf("%lo", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%lo", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_llo)
{
  char buffer[128];
  long a = -(1L << 50);
  int actual_result = ft_printf("%llo", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%llo", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_x)
{
  char buffer[128];
  long a = -1;
  int actual_result = ft_printf("%x", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%x", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hhx)
{
  char buffer[128];
  long a = (1UL << 46) + (1UL << 20);
  int actual_result = ft_printf("%hhx", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hhx", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hx)
{
  char buffer[128];
  long a = -(1UL << 7) - (1UL << 50);
  int actual_result = ft_printf("%hx", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%hx", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_lx)
{
  char buffer[128];
  long a = +(1UL << 15) + (1UL << 44);
  int actual_result = ft_printf("%lx", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%lx", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_llx)
{
  char buffer[128];
  long a = -(1UL << 10) + (1UL << 38);
  int actual_result = ft_printf("%llx", a);
  int expected_result = snprintf(buffer, sizeof buffer, "%llx", a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_X)
{
  char buffer[128];
  const char *format = "%X";
  long a = 0xFa123B4c;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hhX)
{
  char buffer[128];
  const char *format = "%hhX";
  long a = 0x1b4C6D;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_hX)
{
  char buffer[128];
  const char *format = "%hX";
  long a = 0x13e;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_lX)
{
  char buffer[128];
  const char *format = "%lX";
  long a = 0x5E2bF;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_llX)
{
  char buffer[128];
  const char *format = "%llX";
  long a = 0x123E6d;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_pstr_eq(get_write_buf(), buffer);
}
END_TEST

START_TEST(test_single_param_p)
{
  char buffer[128];
  const char *format = "%p";
  int a = 1;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_s_greater)
{
  char buffer[128];
  const char *format = "%14s";
  const char *s = "abcd";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_s_equal)
{
  char buffer[128];
  const char *format = "%5s";
  const char *s = "suPer";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_s_smaller)
{
  char buffer[128];
  const char *format = "%3s";
  const char *s = "smaller";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_d_greater)
{
  char buffer[128];
  const char *format = "%17d";
  int a = 1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_d_equal)
{
  char buffer[128];
  const char *format = "%7d";
  int a = -456321;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_d_smaller)
{
  char buffer[128];
  const char *format = "%4d";
  int a = -4578127;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_u_greater)
{
  char buffer[128];
  const char *format = "%10u";
  unsigned a = 543;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_u_equal)
{
  char buffer[128];
  const char *format = "%6u";
  unsigned a = 555444;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_u_smaller)
{
  char buffer[128];
  const char *format = "%2u";
  unsigned a = 77894;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_o_greater)
{
  char buffer[128];
  const char *format = "%9o";
  unsigned a = 01234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_o_equal)
{
  char buffer[128];
  const char *format = "%1o";
  unsigned a = 2;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_o_smaller)
{
  char buffer[128];
  const char *format = "%3o";
  unsigned a = 0153145;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_x_greater)
{
  char buffer[128];
  const char *format = "%16x";
  unsigned a = 0xf143;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_x_equal)
{
  char buffer[128];
  const char *format = "%4x";
  unsigned a = 0xb5d1;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_x_smaller)
{
  char buffer[128];
  const char *format = "%3x";
  unsigned a = 0xc74ba;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_X_greater)
{
  char buffer[128];
  const char *format = "%14X";
  unsigned a = 0xb4ce;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_X_equal)
{
  char buffer[128];
  const char *format = "%5X";
  unsigned a = 0x62f7D;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_X_smaller)
{
  char buffer[128];
  const char *format = "%2X";
  unsigned a = 0x75Ce4f;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_p_greater)
{
  char buffer[128];
  const char *format = "%20p";
  unsigned a = 7;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_p_equal)
{
  char buffer[128];
  const char *format = "%14p";
  unsigned a = 10;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_p_smaller)
{
  char buffer[128];
  const char *format = "%5p";
  unsigned a = 123;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_c_greater)
{
  char buffer[128];
  const char *format = "%9c";
  char c = '5';
  int actual_result = ft_printf(format, c);
  int expected_result = snprintf(buffer, sizeof buffer, format, c);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_c_equal)
{
  char buffer[128];
  const char *format = "%1c";
  char c = 'y';
  int actual_result = ft_printf(format, c);
  int expected_result = snprintf(buffer, sizeof buffer, format, c);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_s_greater)
{
  char buffer[128];
  const char *format = "%.10s";
  const char *s = "qwerty";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

Suite *ft_printf_suite(void)
{
  Suite *s;
  TCase *tc_single_format_param;
  TCase *tc_single_param;
  TCase *tc_width;
  TCase *tc_precision;

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
  
  tcase_add_test(tc_single_param, test_single_param_min_uint);
  tcase_add_test(tc_single_param, test_single_param_max_uint);
  
  tcase_add_test(tc_single_param, test_single_param_hhd);
  tcase_add_test(tc_single_param, test_single_param_hhi);
  tcase_add_test(tc_single_param, test_single_param_hhu);

  tcase_add_test(tc_single_param, test_single_param_hd);
  tcase_add_test(tc_single_param, test_single_param_hi);
  tcase_add_test(tc_single_param, test_single_param_hu);

  tcase_add_test(tc_single_param, test_single_param_ld);
  tcase_add_test(tc_single_param, test_single_param_li);
  tcase_add_test(tc_single_param, test_single_param_lu);
  
  tcase_add_test(tc_single_param, test_single_param_lld);
  tcase_add_test(tc_single_param, test_single_param_lli);
  tcase_add_test(tc_single_param, test_single_param_llu);
  
  tcase_add_test(tc_single_param, test_single_param_o);
  tcase_add_test(tc_single_param, test_single_param_hho);
  tcase_add_test(tc_single_param, test_single_param_ho);
  tcase_add_test(tc_single_param, test_single_param_lo);
  tcase_add_test(tc_single_param, test_single_param_llo);
   
  tcase_add_test(tc_single_param, test_single_param_x);
  tcase_add_test(tc_single_param, test_single_param_hhx);
  tcase_add_test(tc_single_param, test_single_param_hx);
  tcase_add_test(tc_single_param, test_single_param_lx);
  tcase_add_test(tc_single_param, test_single_param_llx);

  tcase_add_test(tc_single_param, test_single_param_X);
  tcase_add_test(tc_single_param, test_single_param_hhX);
  tcase_add_test(tc_single_param, test_single_param_hX);
  tcase_add_test(tc_single_param, test_single_param_lX);
  tcase_add_test(tc_single_param, test_single_param_llX);
  
  tcase_add_test(tc_single_param, test_single_param_p);

  tc_width = tcase_create("Width");
  tcase_add_checked_fixture(tc_width, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_width, test_width_s_greater);
  tcase_add_test(tc_width, test_width_s_equal);
  tcase_add_test(tc_width, test_width_s_smaller);

  tcase_add_test(tc_width, test_width_d_greater);
  tcase_add_test(tc_width, test_width_d_equal);
  tcase_add_test(tc_width, test_width_d_smaller);

  tcase_add_test(tc_width, test_width_u_greater);
  tcase_add_test(tc_width, test_width_u_equal);
  tcase_add_test(tc_width, test_width_u_smaller);

  tcase_add_test(tc_width, test_width_o_greater);
  tcase_add_test(tc_width, test_width_o_equal);
  tcase_add_test(tc_width, test_width_o_smaller);

  tcase_add_test(tc_width, test_width_x_greater);
  tcase_add_test(tc_width, test_width_x_equal);
  tcase_add_test(tc_width, test_width_x_smaller);

  tcase_add_test(tc_width, test_width_X_greater);
  tcase_add_test(tc_width, test_width_X_equal);
  tcase_add_test(tc_width, test_width_X_smaller);

  tcase_add_test(tc_width, test_width_p_greater);
  tcase_add_test(tc_width, test_width_p_equal);
  tcase_add_test(tc_width, test_width_p_smaller);

  tcase_add_test(tc_width, test_width_c_greater);
  tcase_add_test(tc_width, test_width_c_equal);

  tc_precision = tcase_create("Precision");
  tcase_add_checked_fixture(tc_precision, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_precision, test_precision_s_greater);
  
  suite_add_tcase(s, tc_single_format_param);
  suite_add_tcase(s, tc_single_param);
  suite_add_tcase(s, tc_width);
  suite_add_tcase(s, tc_precision);

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
