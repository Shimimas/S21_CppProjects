#include <gtest/gtest.h>

#include "../Smart_Calc/s21_model.h"

TEST(parser_test, incorrect_point_test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123..", 0).second, false);
}

TEST(parser_test, incorrect_point_test_1) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123.4.", 0).second, false);
}

TEST(parser_test, incorrect_point_test_2) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123.4", 0).second, true);
  ASSERT_EQ(model.smart_calc("123.4", 0).first, 123.4);
}

TEST(parser_test, incorrect_point_test_3) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc(".4", 0).second, false);
}

TEST(parser_test, incorrect_point_test_4) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc(".", 0).second, false);
}

TEST(parser_test, incorrect_point_test_5) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("+.-", 0).second, false);
}

TEST(parser_test, test_6) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("+-245-5+=", 0).second, false);
}

TEST(parser_test, test_7) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("123fds", 0).second, false);
}

TEST(parser_test, test_8) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin(cos(sin(cos(123.124345))))", 0).second, true);
  ASSERT_EQ((int)model.smart_calc("sin(cos(sin(cos(123.124345))))", 0).first, (int)0.676173);
}

TEST(parser_test, test_9) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin.(cos.(sin(cos())))", 0).second, false);
}

TEST(validator_test, test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin(cos(sin(cos()))))", 0).second, false);
}

TEST(validator_test, test_1) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin())(", 0).second, false);
}

TEST(validator_test, test_2) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("sin10", 0).second, false);
}

TEST(exp_number_test, test_0) {
  s21::Model model;
  ASSERT_EQ(model.smart_calc("1.234e-10", 0).second, true);
  ASSERT_EQ(model.smart_calc("1.234e-10", 0).first, 1.234e-10);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}