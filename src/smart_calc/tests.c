#include <check.h>
#include <stdio.h>

#include "calculate.h"

START_TEST(calc_test) {
  {
    char src[100] = "4^acos(x/4)/tan(2*x)";
    double valX = 1.2;
    double result;
    SmartCalc(src, &result, &valX);
    double real_result = -6.31492;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-1 failed");
  }
  {
    char src[100] = "x+x";
    double valX = 2;
    double result;
    SmartCalc(src, &result, &valX);
    double real_result = 4;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-2 failed");
  }
  {
    char src[100] = "123+0.456";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = 123.456;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-3 failed");
  }
  {
    char src[100] = "log(x)";
    double valX = -2;
    double result;
    SmartCalc(src, &result, &valX);
    double real_result = NAN;
    ck_assert_msg(result != result && real_result != real_result,
                  "test-4 failed");
  }
  {
    char src[100] = "-(-1)";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = 1;
    ck_assert_msg(result == real_result, "test-5 failed");
  }
  {
    char src[100] = "cos(10mod2.2)";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = 0.362358;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-6 failed");
  }
  {
    char src[100] = "sqrt(ln(10))";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = 1.517427;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-7 failed");
  }
  {
    char src[100] = "atan(10)+sin(10)";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = 1.644775;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-8 failed");
  }
  {
    char src[100] = "asin(1)";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = 1.570796;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-9 failed");
  }
  {
    char src[100] = "10-20*(-10)";
    double result;
    SmartCalc(src, &result, NULL);
    double real_result = -210;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001,
                  "test-10 failed");
  }
  {
    char src[100] = "4 /";
    double result;
    int flag = SmartCalc(src, &result, NULL);

    ck_assert_msg(flag == 0, "test-11 failed");
  }
  {
    char src[100] = "sin ( 2 / 23.3 ))";
    double result;
    int flag = SmartCalc(src, &result, NULL);

    ck_assert_msg(flag == 0, "test-12 failed");
  }
  {
    char src[100] = "*/+";
    double result;
    int flag = SmartCalc(src, &result, NULL);

    ck_assert_msg(flag == 0, "test-13 failed");
  }
  {
    char src[100] = "sin()";
    double result;
    int flag = SmartCalc(src, &result, NULL);

    ck_assert_msg(flag == 0, "test-14 failed");
  }
  {
    char src[100] = "abracadabra&7";
    double result;
    int flag = SmartCalc(src, &result, NULL);

    ck_assert_msg(flag == 0, "test-15 failed");
  }
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, calc_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
