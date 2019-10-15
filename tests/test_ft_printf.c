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
  ck_assert_pstr_eq(get_write_buf(), "");
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
  ck_assert_pstr_eq(get_write_buf(), "");
}
END_TEST

START_TEST(test_single_param_cstring_null)
{
  char buffer[128];
  const char *format = "%s";
  int actual_result = ft_printf(format, NULL);
  int expected_result = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
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
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
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

START_TEST(test_precision_s_equal)
{
  char buffer[128];
  const char *format = "%.4s";
  const char *s = "abcD";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_s_smaller)
{
  char buffer[128];
  const char *format = "%.3s";
  const char *s = "123456789";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_s_zero)
{
  char buffer[128];
  const char *format = "[%.0s]";
  const char *s = "123456789";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_s_dot)
{
  char buffer[128];
  const char *format = "[%.s]";
  const char *s = "abcdef";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_d_smaller)
{
  char buffer[128];
  const char *format = "[%.3d]";
  int a = 123456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_d_equal)
{
  char buffer[128];
  const char *format = "[%.4d]";
  int a = 9876;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_d_zero)
{
  char buffer[128];
  const char *format = "[%.0d]";
  int a = 123456789;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_d_dot)
{
  char buffer[128];
  const char *format = "[%.d]";
  int a = 123456789;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_d_greater)
{
  char buffer[128];
  const char *format = "[%.10d]";
  int a = 12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_i_greater)
{
  char buffer[128];
  const char *format = "[%.10i]";
  int a = -12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_i_equal)
{
  char buffer[128];
  const char *format = "[%.5i]";
  int a = -98765;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_i_zero)
{
  char buffer[128];
  const char *format = "[%.0i]";
  int a = -5678;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_i_dot)
{
  char buffer[128];
  const char *format = "[%.i]";
  int a = -321;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_i_smaller)
{
  char buffer[128];
  const char *format = "[%.4i]";
  int a = -987654;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_di_zero_arg)
{
  char buffer[128];
  const char *format = "[%.d%.i%.0d%.0i]";
  int a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_di_sharp_zero_arg)
{
  char buffer[128];
  const char *format = "[%#.d%#.i%#.0d%#.0i]";
  int a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST


START_TEST(test_precision_u_greater)
{
  char buffer[128];
  const char *format = "[%.11u]";
  unsigned a = 12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_u_equal)
{
  char buffer[128];
  const char *format = "[%.3u]";
  unsigned a = 543;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_u_zero)
{
  char buffer[128];
  const char *format = "[%.0u]";
  unsigned a = 6789;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_u_dot)
{
  char buffer[128];
  const char *format = "[%.u]";
  unsigned a = 1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_u_smaller)
{
  char buffer[128];
  const char *format = "[%.2u]";
  unsigned a = 987;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_u_zero_arg)
{
  char buffer[128];
  const char *format = "[%.u|%.0u]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_u_sharp_zero_arg)
{
  char buffer[128];
  const char *format = "[%#.u|%#.0u]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_greater)
{
  char buffer[128];
  const char *format = "[%.14o]";
  unsigned a = 0123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_equal)
{
  char buffer[128];
  const char *format = "[%.6o]";
  unsigned a = 0123123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_zero)
{
  char buffer[128];
  const char *format = "[%.0o]";
  unsigned a = 0123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_dot)
{
  char buffer[128];
  const char *format = "[%.o]";
  unsigned a = 0321;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_smaller)
{
  char buffer[128];
  const char *format = "[%.2o]";
  unsigned a = 0567123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_zero_arg)
{
  char buffer[128];
  const char *format = "[%.o|%.0o]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_o_sharp_zero_arg)
{
  char buffer[128];
  const char *format = "[%#.o|%#.0o]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_x_greater)
{
  char buffer[128];
  const char *format = "[%.15x]";
  unsigned a = 0xa12bc;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_x_equal)
{
  char buffer[128];
  const char *format = "[%.5x]";
  unsigned a = 0xc7b32;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_x_zero)
{
  char buffer[128];
  const char *format = "[%.0x]";
  unsigned a = 0x123fe;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_x_dot)
{
  char buffer[128];
  const char *format = "[%.x]";
  unsigned a = 0x567fd;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_x_smaller)
{
  char buffer[128];
  const char *format = "[%.4x]";
  unsigned a = 0xffff15;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_X_greater)
{
  char buffer[128];
  const char *format = "[%.16X]";
  unsigned a = 0x123fe;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_X_equal)
{
  char buffer[128];
  const char *format = "[%.2X]";
  unsigned a = 0xbc;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_X_zero)
{
  char buffer[128];
  const char *format = "[%.0X]";
  unsigned a = 0xfb3b;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_X_dot)
{
  char buffer[128];
  const char *format = "[%.X]";
  unsigned a = 0x56c43;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_X_smaller)
{
  char buffer[128];
  const char *format = "[%.4X]";
  unsigned a = 0x1234df;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_xX_zero_arg)
{
  char buffer[128];
  const char *format = "[%.x|%.0x|%.X|%.0X]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_xX_sharp_zero_arg)
{
  char buffer[128];
  const char *format = "[%#.x|%#.0x|%#.X|%#.0X]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_p_smaller)
{
  char buffer[128];
  const char *format = "[%.3p]";
  unsigned a = 1;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_p_equal)
{
  char buffer[128];
  const char *format = "[%.12p]";
  unsigned a = 1;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_p_zero)
{
  char buffer[128];
  const char *format = "[%.0p]";
  unsigned a = 1;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_p_dot)
{
  char buffer[128];
  const char *format = "[%.p]";
  unsigned a = 1;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_p_greater)
{
  char buffer[128];
  const char *format = "[%.16p]";
  unsigned a = 1;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_precision_p_zero_arg)
{
  const char *format = "[%.p|%.0p]";
  int actual_result = ft_printf(format, NULL, NULL);
  ck_assert_pstr_eq(get_write_buf(), "[0x|0x]");
  ck_assert_int_eq(actual_result, 7);
}
END_TEST

START_TEST(test_precision_p_sharp_zero_arg)
{
  const char *format = "[%#.p|%#.0p]";
  int actual_result = ft_printf(format, NULL, NULL);
  ck_assert_pstr_eq(get_write_buf(), "[0x0|0x0]");
  ck_assert_int_eq(actual_result, 9);
}
END_TEST

START_TEST(test_minus_s)
{
  char buffer[128];
  const char *format = "[%-s]";
  const char *s = "Text";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_s_width_greater)
{
  char buffer[128];
  const char *format = "[%-10s]";
  const char *s = "Text";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_s_width_smaller)
{
  char buffer[128];
  const char *format = "[%-2s]";
  const char *s = "Text";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_s_width_equal)
{
  char buffer[128];
  const char *format = "[%-4s]";
  const char *s = "Text";
  int actual_result = ft_printf(format, s);
  int expected_result = snprintf(buffer, sizeof buffer, format, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_d_width_smaller)
{
  char buffer[128];
  const char *format = "[%-4d]";
  int a = 123456789;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_d_width_equal)
{
  char buffer[128];
  const char *format = "[%-5d]";
  int a = 12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_d_width_greater)
{
  char buffer[128];
  const char *format = "[%-10d]";
  int a = 1234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_i_width_smaller)
{
  char buffer[128];
  const char *format = "[%-4i]";
  int a = -123456789;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_i_width_equal)
{
  char buffer[128];
  const char *format = "[%-5i]";
  int a = -1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_i_width_greater)
{
  char buffer[128];
  const char *format = "[%-10i]";
  int a = -123456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_u_width_smaller)
{
  char buffer[128];
  const char *format = "[%-5u]";
  unsigned a = 123456789;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_u_width_equal)
{
  char buffer[128];
  const char *format = "[%-4u]";
  unsigned a = 1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_u_width_greater)
{
  char buffer[128];
  const char *format = "[%-7u]";
  unsigned a = 123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_o_width_smaller)
{
  char buffer[128];
  const char *format = "[%-2o]";
  unsigned a = 01234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_o_width_equal)
{
  char buffer[128];
  const char *format = "[%-3o]";
  unsigned a = 0123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_o_width_greater)
{
  char buffer[128];
  const char *format = "[%-10o]";
  unsigned a = 0123123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_x_width_smaller)
{
  char buffer[128];
  const char *format = "[%-2x]";
  unsigned a = 0x1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_x_width_equal)
{
  char buffer[128];
  const char *format = "[%-4x]";
  unsigned a = 0xbbbb;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_x_width_greater)
{
  char buffer[128];
  const char *format = "[%-10x]";
  unsigned a = 0xcccccc;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_X_width_smaller)
{
  char buffer[128];
  const char *format = "[%-3X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_X_width_equal)
{
  char buffer[128];
  const char *format = "[%-6X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_X_width_greater)
{
  char buffer[128];
  const char *format = "[%-10X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_p_width_smaller)
{
  char buffer[128];
  const char *format = "[%-5p]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_p_width_equal)
{
  char buffer[128];
  const char *format = "[%-14p]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_p_width_greater)
{
  char buffer[128];
  const char *format = "[%-20p]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, &a);
  int expected_result = snprintf(buffer, sizeof buffer, format, &a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_c_width_equal)
{
  char buffer[128];
  const char *format = "[%-1c]";
  char a = '1';
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_minus_c_width_greater)
{
  char buffer[128];
  const char *format = "[%-5c]";
  char a = '2';
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_d_width_greater)
{
  char buffer[128];
  const char *format = "[%+5d]";
  int a = 123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_d_width_equal)
{
  char buffer[128];
  const char *format = "[%+4d]";
  int a = 123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_d_width_smaller)
{
  char buffer[128];
  const char *format = "[%+2d]";
  int a = 1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_i_width_greater)
{
  char buffer[128];
  const char *format = "[%+5i]";
  int a = -12;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_i_width_equal)
{
  char buffer[128];
  const char *format = "[%+4i]";
  int a = -123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_i_width_smaller)
{
  char buffer[128];
  const char *format = "[%+3i]";
  int a = -123456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_u_width_greater)
{
  char buffer[128];
  const char *format = "[%+5u]";
  unsigned a = 123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_u_width_equal)
{
  char buffer[128];
  const char *format = "[%+3u]";
  unsigned a = 123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_u_width_smaller)
{
  char buffer[128];
  const char *format = "[%+3u]";
  unsigned a = 123456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_o_width_greater)
{
  char buffer[128];
  const char *format = "[%+8o]";
  unsigned a = 01234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_o_width_equal)
{
  char buffer[128];
  const char *format = "[%+4o]";
  unsigned a = 01234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_o_width_smaller)
{
  char buffer[128];
  const char *format = "[%+3o]";
  unsigned a = 01234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_x_width_greater)
{
  char buffer[128];
  const char *format = "[%+10x]";
  unsigned a = 0x1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_x_width_equal)
{
  char buffer[128];
  const char *format = "[%+6x]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_x_width_smaller)
{
  char buffer[128];
  const char *format = "[%+3x]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_X_width_greater)
{
  char buffer[128];
  const char *format = "[%+10X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_X_width_equal)
{
  char buffer[128];
  const char *format = "[%+6X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_plus_X_width_smaller)
{
  char buffer[128];
  const char *format = "[%+3X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_o)
{
  char buffer[128];
  const char *format = "[%#o]";
  unsigned a = 01234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_x)
{
  char buffer[128];
  const char *format = "[%#x]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_X)
{
  char buffer[128];
  const char *format = "[%#X]";
  unsigned a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_f)
{
  char buffer[128];
  const char *format = "[%#.f]";
  double a = 1234.0;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_f_simple)
{
  char buffer[128];
  const char *format = "[%#f] [%#f]";
  double a = -1234.0;
  double b = -123.4567;
  int actual_result = ft_printf(format, a, b);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, b);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_o_arg_zero)
{
  char buffer[128];
  const char *format = "[%#o]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_x_arg_zero)
{
  char buffer[128];
  const char *format = "[%#x]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_pound_X_arg_zero)
{
  char buffer[128];
  const char *format = "[%#X]";
  unsigned a = 0;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_d)
{
  char buffer[128];
  const char *format = "[%0d]";
  int a = 1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_i)
{
  char buffer[128];
  const char *format = "[%0i]";
  int a = -1234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_u)
{
  char buffer[128];
  const char *format = "[%0u]";
  unsigned int a = 1234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_o)
{
  char buffer[128];
  const char *format = "[%0o]";
  unsigned int a = 01234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_x)
{
  char buffer[128];
  const char *format = "[%0x]";
  unsigned int a = 0x1234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_X)
{
  char buffer[128];
  const char *format = "[%0X]";
  unsigned int a = 0x1234567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_d_width_greater)
{
  char buffer[128];
  const char *format = "[%010d]";
  int a = 12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_i_width_greater)
{
  char buffer[128];
  const char *format = "[%010i]";
  int a = -12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_u_width_greater)
{
  char buffer[128];
  const char *format = "[%08u]";
  unsigned a = 12345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_o_width_greater)
{
  char buffer[128];
  const char *format = "[%05o]";
  unsigned a = 0123;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_x_width_greater)
{
  char buffer[128];
  const char *format = "[%07x]";
  unsigned a = 0x123b;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_zero_X_width_greater)
{
  char buffer[128];
  const char *format = "[%07X]";
  unsigned a = 0x123b;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_small_int)
{
  char buffer[128];
  const char *format = "[%f]";
  float a = 123.0;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_small_negative_int)
{
  char buffer[128];
  const char *format = "[%f]";
  float a = -256.0;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_small)
{
  char buffer[128];
  const char *format = "[%f]";
  float a = 123.456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_small_negative)
{
  char buffer[128];
  const char *format = "[%f]";
  double a = -12.34;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_small_precision)
{
  char buffer[128];
  const char *format = "[%.3f]";
  double a = -1.2345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_big_precision)
{
  char buffer[128];
  const char *format = "[%.7f]";
  double a = -1.2345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_width_greater)
{
  char buffer[128];
  const char *format = "[%10f]";
  double a = 1.2345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_width_greater_negative)
{
  char buffer[128];
  const char *format = "[%12f]";
  double a = -1.23456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_width_greater_precision_small)
{
  char buffer[128];
  const char *format = "[%8.3f]";
  double a = -1.22222;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_zero_width_greater_precision_small)
{
  char buffer[128];
  const char *format = "[%09.3f]";
  double a = -1.22222;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_float_minus_width_greater_precision_small)
{
  char buffer[128];
  const char *format = "[%-9.3f]";
  double a = -1.22222;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_lfloat)
{
  char buffer[128];
  const char *format = "[%-9.3lf]";
  double a = -1.22222;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_Lfloat)
{
  char buffer[128];
  const char *format = "[%-9.3Lf]";
  long double a = -1.22222;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_precision0)
{
  char buffer[128];
  const char *format = "[%.f]";
  double a = 1.2345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_precision0_negative)
{
  char buffer[128];
  const char *format = "[%.f]";
  double a = -1.2345;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_precision0_round)
{
  char buffer[128];
  const char *format = "[%.f]";
  double a = 1234.567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_precision0_round_negative)
{
  char buffer[128];
  const char *format = "[%.f]";
  double a = -1234.567;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_round)
{
  char buffer[128];
  const char *format = "[%.2f]";
  double a = 12.3456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_round_negative)
{
  char buffer[128];
  const char *format = "[%.3f]";
  double a = -123.45678;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_max_long_intpart)
{
  char buffer[128];
  const char *format = "%f %lf %Lf";
  long double a = 9223372036854775807.0L;
  int actual_result = ft_printf(format, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_min_long_intpart)
{
  char buffer[256];
  const char *format = "%f %lf %Lf";
  long double a = -9223372036854775808.0L;
  int actual_result = ft_printf(format, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_max_long_floatpart)
{
  char buffer[256];
  const char *format = "%.18f %.18lf %.18Lf";
  long double a = 0.18446744073709551615L;
  int actual_result = ft_printf(format, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_max_long_bothpart)
{
  char buffer[256];
  const char *format = "%.18f %.18lf %.18Lf";
  long double a = 9223372036854775807.18446744073709551615L;
  int actual_result = ft_printf(format, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_min_long_bothpart)
{
  char buffer[256];
  const char *format = "%.18f %.18lf %.18Lf";
  long double a = -9223372036854775808.18446744073709551615L;
  int actual_result = ft_printf(format, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_round_max_bothpart_default_precision)
{
  char buffer[256];
  const char *format = "%f %lf %Lf %f %lf %Lf";
  long double a = 9223372036854775807.18446744073709551615L;
  long double b = -9223372036854775808.18446744073709551615L;
  int actual_result = ft_printf(format, a, a, a, b, b, b);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, b, b, b);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_round_max_bothpart_precision_5)
{
  char buffer[256];
  const char *format = "%.5f %.5lf %.5Lf %.5f %.5lf %.5Lf";
  long double a = 9223372036854775807.18446744073709551615L;
  long double b = -9223372036854775808.18446744073709551615L;
  int actual_result = ft_printf(format, a, a, a, b, b, b);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, b, b, b);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_f_round_max_bothpart_precision_zero)
{
  char buffer[512];
  const char *format = "%.0f %.0lf %.0Lf %.0f %.0lf %.0Lf %.f %.lf %.Lf %.f %.lf %.Lf";
  long double a = 9223372036854775807.18446744073709551615L;
  long double b = -9223372036854775808.18446744073709551615L;
  int actual_result = ft_printf(format, a, a, a, b, b, b, a, a, a, b, b, b);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, b, b, b, a, a, a, b, b, b);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_d)
{
  char buffer[128];
  const char *format = "[% d]";
  int a = 1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_i_negative)
{
  char buffer[128];
  const char *format = "[% i]";
  int a = -1234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_u)
{
  char buffer[128];
  const char *format = "[% u]";
  unsigned int a = 256;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_o)
{
  char buffer[128];
  const char *format = "[% o]";
  unsigned int a = 01234;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_x)
{
  char buffer[128];
  const char *format = "[% x]";
  unsigned int a = 0xabcdef12;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_X)
{
  char buffer[128];
  const char *format = "[% X]";
  unsigned int a = 0xabcdef;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_f)
{
  char buffer[128];
  const char *format = "[% f]";
  double a = 123.456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_lf)
{
  char buffer[128];
  const char *format = "[% lf]";
  double a = -123.456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_single_percent)
{
  char buffer[128];
  const char *format = "[%";
  int actual_result = ft_printf(format);
  int expected_result = snprintf(buffer, sizeof buffer, format);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_Lf)
{
  char buffer[128];
  const char *format = "[% Lf]";
  long double a = -123.456;
  int actual_result = ft_printf(format, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_equal_width)
{
  char buffer[512];
  const char *format = "% 5.5d % 3.3i % 4.4u % 5.5o % 3.3x % 3.3X"
      "% 7.4f % 7.4lf % 2.4c % 5.5s";
  int a = 12;
  int a2 = -1;
  double b = 1.46;
  char c = 'q';
  const char *s = "Hello World!";
  int actual_result =
      ft_printf(format, a, a2, a, a, a, a, b, b, c, s);
  int expected_result =
      snprintf(buffer, sizeof buffer, format, a, a2, a, a, a, a, b, b, c, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_space_minus_equal_width)
{
  char buffer[512];
  const char *format = "%- 5.5d %- 3.3i % -4.4u %- 5.5o %-- 3.3x %- 3.3X"
      "%- 7.4f % -7.4lf %- 2.4c % -5.5s";
  int a = 12;
  int a2 = -1;
  double b = 1.46;
  char c = 'q';
  const char *s = "Hello World!";
  int actual_result =
      ft_printf(format, a, a2, a, a, a, a, b, b, c, s);
  int expected_result =
      snprintf(buffer, sizeof buffer, format, a, a2, a, a, a, a, b, b, c, s);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_omit_type)
{
  char buffer[128];
  const char *format = "[%b123]";
  int actual_result = ft_printf(format);
  int expected_result = snprintf(buffer, sizeof buffer, format);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_width_omit_type)
{
  char buffer[128];
  const char *format = "[%123]";
  int actual_result = ft_printf(format);
  int expected_result = snprintf(buffer, sizeof buffer, format);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_full_unknown_type)
{
  char buffer[128];
  const char *format = "[%#+-123.456r";
  int actual_result = ft_printf(format);
  int expected_result = snprintf(buffer, sizeof buffer, format);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_multi_unknown_type)
{
  char buffer[128];
  const char *format = "My name is %-10s. I am %+5d. [%#+-123.456r How are you? %% %c stop";
  const char *s = "Doit";
  int a = 57;
  char c = 'q';
  int actual_result = ft_printf(format, s, a, c);
  int expected_result = snprintf(buffer, sizeof buffer, format, s, a, c);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_multi_omit_type)
{
  char buffer[128];
  const char *format = "My name is %-10s. I am %+5d. [%#+-123.456 How are you? %% %c stop";
  const char *s = "Doit";
  int a = 57;
  char c = 'q';
  int actual_result = ft_printf(format, s, a, c);
  int expected_result = snprintf(buffer, sizeof buffer, format, s, a, c);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_multi_single_percent)
{
  char buffer[128];
  const char *format = "My name is %-10s. I am %+5d. % How are you? %% %c stop";
  const char *s = "Doit";
  int a = 57;
  char c = 'q';
  int actual_result = ft_printf(format, s, a, c);
  int expected_result = snprintf(buffer, sizeof buffer, format, s, a, c);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_multiflags_zero_precision)
{
  char buffer[128];
  const char *format = "%015.5d %0.4i %0-20.10u %-010.2o %-010.5x %05.10X";
  int a = 123;
  int b = -789;
  unsigned c = 45;
  unsigned d = 012345;
  unsigned e = 0xabc;
  unsigned f = 0x123ab;
  int actual_result = ft_printf(format, a, b, c, d, e, f);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, b, c, d, e, f);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_multiflags_plus_space)
{
  char buffer[128];
  const char *format = "% + 15.5d % +.4i % +-  20.10u %-10+o %+-+ 10.5x %+ +5.10X";
  int a = 123;
  int b = -789;
  unsigned c = 45;
  unsigned d = 012345;
  unsigned e = 0xabc;
  unsigned f = 0x123ab;
  int actual_result = ft_printf(format, a, b, c, d, e, f);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, b, c, d, e, f);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_multiflags_width_precision_p)
{
  char buffer[128];
  const char *format = "%p %.10p %15.7p %015.7p\n";
  unsigned long a = 0xf00c;
  void *p = (void *) a;
  int actual_result = ft_printf(format, p, p, p, p);
  int expected_result = snprintf(buffer, sizeof buffer, format, p, p, p, p);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_int)
{
  char buffer[128];
  const char *format = "%d %i";
  int a = 2147483647;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_int)
{
  char buffer[128];
  const char *format = "%d %i";
  int a = -2147483648;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_zero_int)
{
  char buffer[128];
  const char *format = "%d %i";
  int a = 0;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_uint)
{
  char buffer[128];
  const char *format = "%u %o %x %X";
  unsigned a = 4294967295;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_uint)
{
  char buffer[128];
  const char *format = "%u %o %x %X";
  unsigned a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_long)
{
  char buffer[128];
  const char *format = "%ld %li %lld %lli";
  long a = 9223372036854775807L;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_long)
{
  char buffer[128];
  const char *format = "%ld %li %lld %lli";
  long a = 0x8000000000000000L;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_zero_long)
{
  char buffer[128];
  const char *format = "%ld %li %lld %lli";
  long a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_ulong)
{
  char buffer[256];
  const char *format = "%lu %lo %lx %lX %llu %llo %llx %llX";
  unsigned long a = 18446744073709551615UL;
  int actual_result = ft_printf(format, a, a, a, a, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_ulong)
{
  char buffer[256];
  const char *format = "%lu %lo %lx %lX %llu %llo %llx %llX";
  unsigned long a = 0;
  int actual_result = ft_printf(format, a, a, a, a, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_hhd)
{
  char buffer[256];
  const char *format = "%hhd %hhi";
  long a = 128;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_hhd)
{
  char buffer[256];
  const char *format = "%hhd %hhi";
  long a = -129;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_hhu)
{
  char buffer[256];
  const char *format = "%hhu %hho %hhx %hhX";
  unsigned long a = 128;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_hhu)
{
  char buffer[256];
  const char *format = "%hhu %hho %hhx %hhX";
  long a = -1;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_hd)
{
  char buffer[256];
  const char *format = "%hd %hi";
  long a = 32768;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_hd)
{
  char buffer[256];
  const char *format = "%hd %hi";
  long a = -32769;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_hu)
{
  char buffer[256];
  const char *format = "%hu %ho %hx %hX";
  long a = 65536;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_hu)
{
  char buffer[256];
  const char *format = "%hu %ho %hx %hX";
  long a = -1;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_d)
{
  char buffer[256];
  const char *format = "%d %i";
  long a = 2147483648L;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_d)
{
  char buffer[256];
  const char *format = "%d %i";
  long a = -2147483649L;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_u)
{
  char buffer[256];
  const char *format = "%u %o %x %X";
  long a = 4294967296L;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_u)
{
  char buffer[256];
  const char *format = "%u %o %x %X";
  long a = -1;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_above_ld)
{
  char buffer[256];
  const char *format = "%ld %li %lld %lli";
  unsigned long a = 9223372036854775808UL;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_one_below_lu)
{
  char buffer[256];
  const char *format = "%lu %lo %lx %lX %llu %llo %llx %llX";
  long a = -1;
  int actual_result = ft_printf(format, a, a, a, a, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_short)
{
  char buffer[256];
  const char *format = "%hd %hi";
  long a = 32767;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_short)
{
  char buffer[256];
  const char *format = "%hd %hi";
  long a = -32768;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_ushort)
{
  char buffer[256];
  const char *format = "%hu %ho %hx %hX";
  long a = 65535;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_ushort)
{
  char buffer[256];
  const char *format = "%hu %ho %hx %hX";
  long a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_char)
{
  char buffer[256];
  const char *format = "%hhd %hhi";
  long a = 127;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_char)
{
  char buffer[256];
  const char *format = "%hhd %hhi";
  long a = -127;
  int actual_result = ft_printf(format, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_max_uchar)
{
  char buffer[256];
  const char *format = "%hhu %hho %hhx %hhX";
  long a = 255;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_limits_min_uchar)
{
  char buffer[256];
  const char *format = "%hhu %hho %hhx %hhX";
  long a = 0;
  int actual_result = ft_printf(format, a, a, a, a);
  int expected_result = snprintf(buffer, sizeof buffer, format, a, a, a, a);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_other_sharp_o_precision)
{
  char buffer[256];
  const char *format = "test%#.4o et %02o %0#14.0o!!";
  int actual_result = ft_printf(format, 012, 036, 12587499);
  int expected_result = snprintf(buffer, sizeof buffer, format, 012, 036, 12587499);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_other_sharp_x_precision)
{
  char buffer[256];
  int ac = ft_printf("cc%#.4X et %#0012x %#04hX !!", 0xaef, 0xe, (unsigned short)0);
  int ex = snprintf(buffer, sizeof buffer,
		    "cc%#.4X et %#0012x %#04hX !!", 0xaef, 0xe, (unsigned short)0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_other_sharp_x_all_precision)
{
  char buffer[256];
  int ac = ft_printf("%0#10.0x", 0);
  int ex = snprintf(buffer, sizeof buffer, "%0#10.0x", 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_other_sharp_o_all_precision)
{
  char buffer[256];
  const char *format = "%0#10.0o %-0#10.0o %0#10.5o %-0#10.5o %10.20o";
  int ac = ft_printf(format, 0, 0, 0, 0, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0, 0, 0, 0, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_single)
{
  char buffer[256];
  const char *format = "%s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_fmt_single)
{
  char buffer[256];
  const char *format = "hello, %s.";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width32)
{
  char buffer[256];
  const char *format = "%32s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width2)
{
  char buffer[256];
  const char *format = "%2s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus32)
{
  char buffer[256];
  const char *format = "%-32s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus16)
{
  char buffer[256];
  const char *format = "%-16s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus3)
{
  char buffer[256];
  const char *format = "%-3s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_09)
{
  char buffer[256];
  const char *format = "%.09s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width3_pre0)
{
  char buffer[256];
  const char *format = "%3.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width10_pre0)
{
  char buffer[256];
  const char *format = "%10.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width1_pre0)
{
  char buffer[256];
  const char *format = "%1.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width2_pre0)
{
  char buffer[256];
  const char *format = "%2.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width9_pre0)
{
  char buffer[256];
  const char *format = "%9.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus3_pre0)
{
  char buffer[256];
  const char *format = "%-3.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus8_pre0)
{
  char buffer[256];
  const char *format = "%-8.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus1_pre0)
{
  char buffer[256];
  const char *format = "%-1.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus2_pre0)
{
  char buffer[256];
  const char *format = "%-2.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus6_pre0)
{
  char buffer[256];
  const char *format = "%-6.s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width3_pre1)
{
  char buffer[256];
  const char *format = "%3.1s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width9_pre1)
{
  char buffer[256];
  const char *format = "%9.1s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus3_pre1)
{
  char buffer[256];
  const char *format = "%-3.1s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus9_pre1)
{
  char buffer[256];
  const char *format = "%-9.1s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus6_pre1)
{
  char buffer[256];
  const char *format = "%-6.1s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width3_pre6)
{
  char buffer[256];
  const char *format = "%3.6s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width20_pre6)
{
  char buffer[256];
  const char *format = "%20.6s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width6_pre6)
{
  char buffer[256];
  const char *format = "%6.6s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus3_pre8)
{
  char buffer[256];
  const char *format = "%-3.8s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nulls_width_minus10_pre8)
{
  char buffer[256];
  const char *format = "%-10.8s";
  int ac = ft_printf(format, NULL);
  int ex = snprintf(buffer, sizeof buffer, format, NULL);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width1_pre0)
{
  char buffer[256];
  const char *format = "%1.s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width2_pre0)
{
  char buffer[256];
  const char *format = "%2.s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width9_pre0)
{
  char buffer[256];
  const char *format = "%9.s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_minus1_pre0)
{
  char buffer[256];
  const char *format = "%-1.s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_minus2_pre0)
{
  char buffer[256];
  const char *format = "%-2.s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_minus6_pre0)
{
  char buffer[256];
  const char *format = "%-6.s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_minus3_pre1)
{
  char buffer[256];
  const char *format = "%-3.1s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_minus6_pre1)
{
  char buffer[256];
  const char *format = "%-6.1s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_3_pre6)
{
  char buffer[256];
  const char *format = "%3.6s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullchar_width_6_pre6)
{
  char buffer[256];
  const char *format = "%6.6s";
  int ac = ft_printf(format, "");
  int ex = snprintf(buffer, sizeof buffer, format, "");
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width5_pre0)
{
  char buffer[64];
  const char *format = "%5.0i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width5_predot)
{
  char buffer[64];
  const char *format = "%5.i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width_minus5_pre0)
{
  char buffer[64];
  const char *format = "%-5.0i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width_minus5_predot)
{
  char buffer[64];
  const char *format = "%-5.i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width5_plus_pre0)
{
  char buffer[64];
  const char *format = "%+5.0i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width5_plus_predot)
{
  char buffer[64];
  const char *format = "%+5.i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width_minus5_plus_pre0)
{
  char buffer[64];
  const char *format = "%+-5.0i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullint_width_minus5_plus_predot)
{
  char buffer[64];
  const char *format = "%+-5.i";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullu_width5_pre0)
{
  char buffer[64];
  const char *format = "%5.0u";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

START_TEST(test_nullu_width5_predot)
{
  char buffer[64];
  const char *format = "%5.u";
  int ac = ft_printf(format, 0);
  int ex = snprintf(buffer, sizeof buffer, format, 0);
  ck_assert_pstr_eq(get_write_buf(), buffer);
  ck_assert_int_eq(ac, ex);
}
END_TEST

Suite *ft_printf_suite(void)
{
  Suite *s;
  TCase *tc_single_format_param;
  TCase *tc_single_param;
  TCase *tc_width;
  TCase *tc_precision;
  TCase *tc_minus;
  TCase *tc_plus;
  TCase *tc_pound;
  TCase *tc_zero;
  TCase *tc_float;
  TCase *tc_space;
  TCase *tc_error_type;
  TCase *tc_multiflags;
  TCase *tc_limits;
  TCase *tc_other;
  TCase *tc_nulls;
  TCase *tc_nullchar;
  TCase *tc_nullint;
  TCase *tc_nullu;

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
  tcase_add_test(tc_single_param, test_single_param_cstring_null);
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
  tcase_add_test(tc_precision, test_precision_s_equal);
  tcase_add_test(tc_precision, test_precision_s_smaller);
  tcase_add_test(tc_precision, test_precision_s_zero);
  tcase_add_test(tc_precision, test_precision_s_dot);

  tcase_add_test(tc_precision, test_precision_d_smaller);
  tcase_add_test(tc_precision, test_precision_d_equal);
  tcase_add_test(tc_precision, test_precision_d_zero);
  tcase_add_test(tc_precision, test_precision_d_dot);
  tcase_add_test(tc_precision, test_precision_d_greater);

  tcase_add_test(tc_precision, test_precision_i_greater);
  tcase_add_test(tc_precision, test_precision_i_equal);
  tcase_add_test(tc_precision, test_precision_i_zero);
  tcase_add_test(tc_precision, test_precision_i_dot);
  tcase_add_test(tc_precision, test_precision_i_smaller);
  tcase_add_test(tc_precision, test_precision_di_zero_arg);
  tcase_add_test(tc_precision, test_precision_di_sharp_zero_arg);

  tcase_add_test(tc_precision, test_precision_u_greater);
  tcase_add_test(tc_precision, test_precision_u_equal);
  tcase_add_test(tc_precision, test_precision_u_zero);
  tcase_add_test(tc_precision, test_precision_u_dot);
  tcase_add_test(tc_precision, test_precision_u_smaller);
  tcase_add_test(tc_precision, test_precision_u_zero_arg);
  tcase_add_test(tc_precision, test_precision_u_sharp_zero_arg);

  tcase_add_test(tc_precision, test_precision_o_greater);
  tcase_add_test(tc_precision, test_precision_o_equal);
  tcase_add_test(tc_precision, test_precision_o_zero);
  tcase_add_test(tc_precision, test_precision_o_dot);
  tcase_add_test(tc_precision, test_precision_o_smaller);
  tcase_add_test(tc_precision, test_precision_o_zero_arg);
  tcase_add_test(tc_precision, test_precision_o_sharp_zero_arg);

  tcase_add_test(tc_precision, test_precision_x_greater);
  tcase_add_test(tc_precision, test_precision_x_equal);
  tcase_add_test(tc_precision, test_precision_x_zero);
  tcase_add_test(tc_precision, test_precision_x_dot);
  tcase_add_test(tc_precision, test_precision_x_smaller);

  tcase_add_test(tc_precision, test_precision_X_greater);
  tcase_add_test(tc_precision, test_precision_X_equal);
  tcase_add_test(tc_precision, test_precision_X_zero);
  tcase_add_test(tc_precision, test_precision_X_dot);
  tcase_add_test(tc_precision, test_precision_X_smaller);
  tcase_add_test(tc_precision, test_precision_xX_zero_arg);
  tcase_add_test(tc_precision, test_precision_xX_sharp_zero_arg);

  tcase_add_test(tc_precision, test_precision_p_smaller);
  tcase_add_test(tc_precision, test_precision_p_equal);
  tcase_add_test(tc_precision, test_precision_p_zero);
  tcase_add_test(tc_precision, test_precision_p_dot);
  tcase_add_test(tc_precision, test_precision_p_greater);
  tcase_add_test(tc_precision, test_precision_p_zero_arg);
  tcase_add_test(tc_precision, test_precision_p_sharp_zero_arg);

  tc_minus = tcase_create("Minus");
  tcase_add_checked_fixture(tc_minus, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_minus, test_minus_s);
  tcase_add_test(tc_minus, test_minus_s_width_greater);
  tcase_add_test(tc_minus, test_minus_s_width_smaller);
  tcase_add_test(tc_minus, test_minus_s_width_equal);

  tcase_add_test(tc_minus, test_minus_d_width_smaller);
  tcase_add_test(tc_minus, test_minus_d_width_equal);
  tcase_add_test(tc_minus, test_minus_d_width_greater);

  tcase_add_test(tc_minus, test_minus_i_width_smaller);
  tcase_add_test(tc_minus, test_minus_i_width_equal);
  tcase_add_test(tc_minus, test_minus_i_width_greater);

  tcase_add_test(tc_minus, test_minus_u_width_smaller);
  tcase_add_test(tc_minus, test_minus_u_width_equal);
  tcase_add_test(tc_minus, test_minus_u_width_greater);

  tcase_add_test(tc_minus, test_minus_o_width_smaller);
  tcase_add_test(tc_minus, test_minus_o_width_equal);
  tcase_add_test(tc_minus, test_minus_o_width_greater);

  tcase_add_test(tc_minus, test_minus_x_width_smaller);
  tcase_add_test(tc_minus, test_minus_x_width_equal);
  tcase_add_test(tc_minus, test_minus_x_width_greater);

  tcase_add_test(tc_minus, test_minus_X_width_smaller);
  tcase_add_test(tc_minus, test_minus_X_width_equal);
  tcase_add_test(tc_minus, test_minus_X_width_greater);

  tcase_add_test(tc_minus, test_minus_p_width_smaller);
  tcase_add_test(tc_minus, test_minus_p_width_equal);
  tcase_add_test(tc_minus, test_minus_p_width_greater);

  tcase_add_test(tc_minus, test_minus_c_width_equal);
  tcase_add_test(tc_minus, test_minus_c_width_greater);

  tc_plus = tcase_create("Plus");
  tcase_add_checked_fixture(tc_plus, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_plus, test_plus_d_width_greater);
  tcase_add_test(tc_plus, test_plus_d_width_equal);
  tcase_add_test(tc_plus, test_plus_d_width_smaller);

  tcase_add_test(tc_plus, test_plus_i_width_greater);
  tcase_add_test(tc_plus, test_plus_i_width_equal);
  tcase_add_test(tc_plus, test_plus_i_width_smaller);

  tcase_add_test(tc_plus, test_plus_u_width_greater);
  tcase_add_test(tc_plus, test_plus_u_width_equal);
  tcase_add_test(tc_plus, test_plus_u_width_smaller);

  tcase_add_test(tc_plus, test_plus_o_width_greater);
  tcase_add_test(tc_plus, test_plus_o_width_equal);
  tcase_add_test(tc_plus, test_plus_o_width_smaller);

  tcase_add_test(tc_plus, test_plus_x_width_greater);
  tcase_add_test(tc_plus, test_plus_x_width_equal);
  tcase_add_test(tc_plus, test_plus_x_width_smaller);

  tcase_add_test(tc_plus, test_plus_X_width_greater);
  tcase_add_test(tc_plus, test_plus_X_width_equal);
  tcase_add_test(tc_plus, test_plus_X_width_smaller);

  tc_pound = tcase_create("Pound");
  tcase_add_checked_fixture(tc_pound, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_pound, test_pound_o);
  tcase_add_test(tc_pound, test_pound_x);
  tcase_add_test(tc_pound, test_pound_X);
  tcase_add_test(tc_pound, test_pound_f);
  tcase_add_test(tc_pound, test_pound_f_simple);
  tcase_add_test(tc_pound, test_pound_o_arg_zero);
  tcase_add_test(tc_pound, test_pound_x_arg_zero);
  tcase_add_test(tc_pound, test_pound_X_arg_zero);

  tc_zero = tcase_create("Zero");
  tcase_add_checked_fixture(tc_zero, setup_ft_printf, teardown_ft_printf);

  tcase_add_test(tc_zero, test_zero_d);
  tcase_add_test(tc_zero, test_zero_i);
  tcase_add_test(tc_zero, test_zero_u);
  tcase_add_test(tc_zero, test_zero_o);
  tcase_add_test(tc_zero, test_zero_x);
  tcase_add_test(tc_zero, test_zero_X);
  tcase_add_test(tc_zero, test_zero_d_width_greater);
  tcase_add_test(tc_zero, test_zero_i_width_greater);
  tcase_add_test(tc_zero, test_zero_u_width_greater);
  tcase_add_test(tc_zero, test_zero_o_width_greater);
  tcase_add_test(tc_zero, test_zero_x_width_greater);
  tcase_add_test(tc_zero, test_zero_X_width_greater);

  tc_float = tcase_create("Float");
  tcase_add_checked_fixture(tc_float, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_float, test_float_small_int);
  tcase_add_test(tc_float, test_float_small_negative_int);
  tcase_add_test(tc_float, test_float_small);
  tcase_add_test(tc_float, test_float_small_negative);
  tcase_add_test(tc_float, test_float_small_precision);
  tcase_add_test(tc_float, test_float_big_precision);
  tcase_add_test(tc_float, test_float_width_greater);
  tcase_add_test(tc_float, test_float_width_greater_negative);
  tcase_add_test(tc_float, test_float_width_greater_precision_small);
  tcase_add_test(tc_float, test_float_zero_width_greater_precision_small);
  tcase_add_test(tc_float, test_float_minus_width_greater_precision_small);
  tcase_add_test(tc_float, test_lfloat);
  tcase_add_test(tc_float, test_Lfloat);
  tcase_add_test(tc_float, test_f_precision0);
  tcase_add_test(tc_float, test_f_precision0_negative);
  tcase_add_test(tc_float, test_f_precision0_round);
  tcase_add_test(tc_float, test_f_precision0_round_negative);
  tcase_add_test(tc_float, test_f_round);
  tcase_add_test(tc_float, test_f_round_negative);
  tcase_add_test(tc_float, test_f_max_long_intpart);
  tcase_add_test(tc_float, test_f_min_long_intpart);
  tcase_add_test(tc_float, test_f_max_long_floatpart);
  tcase_add_test(tc_float, test_f_max_long_bothpart);
  tcase_add_test(tc_float, test_f_min_long_bothpart);
  tcase_add_test(tc_float, test_f_round_max_bothpart_default_precision);
  tcase_add_test(tc_float, test_f_round_max_bothpart_precision_5);
  tcase_add_test(tc_float, test_f_round_max_bothpart_precision_zero);

  tc_space = tcase_create("Space");
  tcase_add_checked_fixture(tc_space, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_space, test_space_d);
  tcase_add_test(tc_space, test_space_i_negative);
  tcase_add_test(tc_space, test_space_u);
  tcase_add_test(tc_space, test_space_o);
  tcase_add_test(tc_space, test_space_x);
  tcase_add_test(tc_space, test_space_X);
  tcase_add_test(tc_space, test_space_f);
  tcase_add_test(tc_space, test_space_lf);
  tcase_add_test(tc_space, test_space_Lf);
  tcase_add_test(tc_space, test_space_equal_width);
  tcase_add_test(tc_space, test_space_minus_equal_width);

  tc_error_type = tcase_create("Error type");
  tcase_add_checked_fixture(tc_error_type, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_error_type, test_single_percent);
  tcase_add_test(tc_error_type, test_omit_type);
  tcase_add_test(tc_error_type, test_width_omit_type);
  tcase_add_test(tc_error_type, test_full_unknown_type);
  tcase_add_test(tc_error_type, test_multi_unknown_type);
  tcase_add_test(tc_error_type, test_multi_omit_type);
  tcase_add_test(tc_error_type, test_multi_single_percent);

  tc_multiflags = tcase_create("Multi flags");
  tcase_add_checked_fixture(tc_multiflags, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_multiflags, test_multiflags_zero_precision);
  tcase_add_test(tc_multiflags, test_multiflags_plus_space);
  tcase_add_test(tc_multiflags, test_multiflags_width_precision_p);

  tc_limits = tcase_create("Limits");
  tcase_add_checked_fixture(tc_limits, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_limits, test_limits_max_int);
  tcase_add_test(tc_limits, test_limits_min_int);
  tcase_add_test(tc_limits, test_limits_zero_int);
  tcase_add_test(tc_limits, test_limits_max_uint);
  tcase_add_test(tc_limits, test_limits_min_uint);
  tcase_add_test(tc_limits, test_limits_max_long);
  tcase_add_test(tc_limits, test_limits_min_long);
  tcase_add_test(tc_limits, test_limits_zero_long);
  tcase_add_test(tc_limits, test_limits_max_ulong);
  tcase_add_test(tc_limits, test_limits_min_ulong);
  tcase_add_test(tc_limits, test_limits_one_above_hhd);
  tcase_add_test(tc_limits, test_limits_one_below_hhd);
  tcase_add_test(tc_limits, test_limits_one_above_hhu);
  tcase_add_test(tc_limits, test_limits_one_below_hhu);
  tcase_add_test(tc_limits, test_limits_one_above_hd);
  tcase_add_test(tc_limits, test_limits_one_below_hd);
  tcase_add_test(tc_limits, test_limits_one_above_hu);
  tcase_add_test(tc_limits, test_limits_one_below_hu);
  tcase_add_test(tc_limits, test_limits_one_above_d);
  tcase_add_test(tc_limits, test_limits_one_below_d);
  tcase_add_test(tc_limits, test_limits_one_above_u);
  tcase_add_test(tc_limits, test_limits_one_below_u);
  tcase_add_test(tc_limits, test_limits_one_above_ld);
  tcase_add_test(tc_limits, test_limits_one_below_lu);
  tcase_add_test(tc_limits, test_limits_max_short);
  tcase_add_test(tc_limits, test_limits_min_short);
  tcase_add_test(tc_limits, test_limits_max_ushort);
  tcase_add_test(tc_limits, test_limits_min_ushort);
  tcase_add_test(tc_limits, test_limits_max_char);
  tcase_add_test(tc_limits, test_limits_min_char);
  tcase_add_test(tc_limits, test_limits_max_uchar);
  tcase_add_test(tc_limits, test_limits_min_uchar);

  tc_other = tcase_create("Other");
  tcase_add_checked_fixture(tc_other, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_other, test_other_sharp_o_precision);
  tcase_add_test(tc_other, test_other_sharp_x_precision);
  tcase_add_test(tc_other, test_other_sharp_x_all_precision);
  tcase_add_test(tc_other, test_other_sharp_o_all_precision);

  tc_nulls = tcase_create("NULL %s");
  tcase_add_checked_fixture(tc_nulls, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_nulls, test_nulls_single);
  tcase_add_test(tc_nulls, test_nulls_fmt_single);
  tcase_add_test(tc_nulls, test_nulls_width32);
  tcase_add_test(tc_nulls, test_nulls_width2);
  tcase_add_test(tc_nulls, test_nulls_width_minus32);
  tcase_add_test(tc_nulls, test_nulls_width_minus16);
  tcase_add_test(tc_nulls, test_nulls_width_minus3);
  tcase_add_test(tc_nulls, test_nulls_width_09);
  tcase_add_test(tc_nulls, test_nulls_width3_pre0);
  tcase_add_test(tc_nulls, test_nulls_width10_pre0);
  tcase_add_test(tc_nulls, test_nulls_width1_pre0);
  tcase_add_test(tc_nulls, test_nulls_width2_pre0);
  tcase_add_test(tc_nulls, test_nulls_width9_pre0);
  tcase_add_test(tc_nulls, test_nulls_width_minus3_pre0);
  tcase_add_test(tc_nulls, test_nulls_width_minus8_pre0);
  tcase_add_test(tc_nulls, test_nulls_width_minus1_pre0);
  tcase_add_test(tc_nulls, test_nulls_width_minus2_pre0);
  tcase_add_test(tc_nulls, test_nulls_width_minus6_pre0);
  tcase_add_test(tc_nulls, test_nulls_width3_pre1);
  tcase_add_test(tc_nulls, test_nulls_width9_pre1);
  tcase_add_test(tc_nulls, test_nulls_width_minus3_pre1);
  tcase_add_test(tc_nulls, test_nulls_width_minus9_pre1);
  tcase_add_test(tc_nulls, test_nulls_width_minus6_pre1);
  tcase_add_test(tc_nulls, test_nulls_width3_pre6);
  tcase_add_test(tc_nulls, test_nulls_width20_pre6);
  tcase_add_test(tc_nulls, test_nulls_width6_pre6);
  tcase_add_test(tc_nulls, test_nulls_width_minus3_pre8);
  tcase_add_test(tc_nulls, test_nulls_width_minus10_pre8);

  tc_nullchar = tcase_create("nullchar");
  tcase_add_checked_fixture(tc_nullchar, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_nullchar, test_nullchar_width1_pre0);
  tcase_add_test(tc_nullchar, test_nullchar_width2_pre0);
  tcase_add_test(tc_nullchar, test_nullchar_width9_pre0);
  tcase_add_test(tc_nullchar, test_nullchar_width_minus1_pre0);
  tcase_add_test(tc_nullchar, test_nullchar_width_minus2_pre0);
  tcase_add_test(tc_nullchar, test_nullchar_width_minus6_pre0);
  tcase_add_test(tc_nullchar, test_nullchar_width_minus3_pre1);
  tcase_add_test(tc_nullchar, test_nullchar_width_minus6_pre1);
  tcase_add_test(tc_nullchar, test_nullchar_width_3_pre6);
  tcase_add_test(tc_nullchar, test_nullchar_width_6_pre6);

  tc_nullint = tcase_create("nullint");
  tcase_add_checked_fixture(tc_nullint, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_nullint, test_nullint_width5_pre0);
  tcase_add_test(tc_nullint, test_nullint_width5_predot);
  tcase_add_test(tc_nullint, test_nullint_width_minus5_pre0);
  tcase_add_test(tc_nullint, test_nullint_width_minus5_predot);
  tcase_add_test(tc_nullint, test_nullint_width5_plus_pre0);
  tcase_add_test(tc_nullint, test_nullint_width5_plus_predot);
  tcase_add_test(tc_nullint, test_nullint_width_minus5_plus_pre0);
  tcase_add_test(tc_nullint, test_nullint_width_minus5_plus_predot);

  tc_nullu = tcase_create("nullu");
  tcase_add_checked_fixture(tc_nullu, setup_ft_printf, teardown_ft_printf);
  tcase_add_test(tc_nullu, test_nullu_width5_pre0);
  tcase_add_test(tc_nullu, test_nullu_width5_predot);
  
  suite_add_tcase(s, tc_single_format_param);
  suite_add_tcase(s, tc_single_param);
  suite_add_tcase(s, tc_width);
  suite_add_tcase(s, tc_precision);
  suite_add_tcase(s, tc_minus);
  suite_add_tcase(s, tc_plus);
  suite_add_tcase(s, tc_pound);
  suite_add_tcase(s, tc_zero);
  suite_add_tcase(s, tc_float);
  suite_add_tcase(s, tc_space);
  suite_add_tcase(s, tc_error_type);
  suite_add_tcase(s, tc_multiflags);
  suite_add_tcase(s, tc_limits);
  suite_add_tcase(s, tc_other);
  suite_add_tcase(s, tc_nulls);
  suite_add_tcase(s, tc_nullchar);
  suite_add_tcase(s, tc_nullint);
  suite_add_tcase(s, tc_nullu);

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
