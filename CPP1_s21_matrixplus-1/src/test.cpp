#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(create_test, default_constructor) {
  S21Matrix test;
  ASSERT_DOUBLE_EQ(test.GetRows(), 3);
  ASSERT_DOUBLE_EQ(test.GetCols(), 3);
}

TEST(create_test, param_constructor) {
  S21Matrix test(5, 4);
  ASSERT_DOUBLE_EQ(test.GetRows(), 5);
  ASSERT_DOUBLE_EQ(test.GetCols(), 4);
}

TEST(create_test, copy_constructor) {
  S21Matrix test(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  S21Matrix test1(test);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test1.GetMatrix(i, j) != test.GetMatrix(i, j)) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(create_test, move_constructor) {
  S21Matrix test(5, 4);
  S21Matrix tmp(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      tmp.SetMatrix(i, j, i);
    }
  }
  S21Matrix test1(std::move(test));
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test1.GetMatrix(i, j) != i) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(get_set_test, rows_set_get) {
  S21Matrix test;
  test.SetRows(2);
  ASSERT_DOUBLE_EQ(test.GetRows(), 2);
}

TEST(get_set_test, cols_set_get) {
  S21Matrix test;
  test.SetCols(2);
  ASSERT_DOUBLE_EQ(test.GetCols(), 2);
}

TEST(get_set_test, matrix_set_get) {
  S21Matrix test;
  test.SetMatrix(2, 2, 1);
  ASSERT_DOUBLE_EQ(test.GetMatrix(2, 2), 1);
}

TEST(operation_test, sum_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  S21Matrix tmp(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      tmp.SetMatrix(i, j, 2 * i);
    }
  }
  test.SumMatrix(test1);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test.GetMatrix(i, j) != tmp.GetMatrix(i, j)) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, eq_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  int a = test.EqMatrix(test1);
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, sub_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  test.SubMatrix(test1);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test.GetMatrix(i, j) != 0) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, mul_num_matrix) {
  S21Matrix test(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  test.MulNumber(-1);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test.GetMatrix(i, j) != i * -1) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, mul_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(4, 5);
  double b[25] = {0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 18, 18, 18, 18, 18, 24, 24, 24, 24, 24};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  test.MulMatrix(test1);
  int a = 1;
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      if (test.GetMatrix(i, j) != b[test.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, transpose_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(4, 5);
  double b[20] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  test1 = test.Transpose();
  int a = 1;
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      if (test1.GetMatrix(i, j) != b[test1.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, determ_matrix) {
  S21Matrix test(5, 5);
  test.SetMatrix(0, 0, 1);
  test.SetMatrix(0, 1, 2);
  test.SetMatrix(0, 2, 3);
  test.SetMatrix(0, 3, 4);
  test.SetMatrix(0, 4, 5);
  test.SetMatrix(1, 0, 2);
  test.SetMatrix(1, 1, 2);
  test.SetMatrix(1, 2, 3);
  test.SetMatrix(1, 3, 4);
  test.SetMatrix(1, 4, 5);
  test.SetMatrix(2, 0, 3);
  test.SetMatrix(2, 1, 3);
  test.SetMatrix(2, 2, 3);
  test.SetMatrix(2, 3, 4);
  test.SetMatrix(2, 4, 5);
  test.SetMatrix(3, 0, 4);
  test.SetMatrix(3, 1, 4);
  test.SetMatrix(3, 2, 4);
  test.SetMatrix(3, 3, 4);
  test.SetMatrix(3, 4, 5);
  test.SetMatrix(4, 0, 5);
  test.SetMatrix(4, 1, 5);
  test.SetMatrix(4, 2, 5);
  test.SetMatrix(4, 3, 5);
  test.SetMatrix(4, 4, 5);
  EXPECT_TRUE(test.Determinant() == 5);
}

TEST(operation_test, complements_matrix) {
  S21Matrix test(5, 5);
  S21Matrix test1(5, 5);
  test.SetMatrix(0, 0, 1);
  test.SetMatrix(0, 1, 2);
  test.SetMatrix(0, 2, 3);
  test.SetMatrix(0, 3, 4);
  test.SetMatrix(0, 4, 5);
  test.SetMatrix(1, 0, 2);
  test.SetMatrix(1, 1, 2);
  test.SetMatrix(1, 2, 3);
  test.SetMatrix(1, 3, 4);
  test.SetMatrix(1, 4, 5);
  test.SetMatrix(2, 0, 3);
  test.SetMatrix(2, 1, 3);
  test.SetMatrix(2, 2, 3);
  test.SetMatrix(2, 3, 4);
  test.SetMatrix(2, 4, 5);
  test.SetMatrix(3, 0, 4);
  test.SetMatrix(3, 1, 4);
  test.SetMatrix(3, 2, 4);
  test.SetMatrix(3, 3, 4);
  test.SetMatrix(3, 4, 5);
  test.SetMatrix(4, 0, 5);
  test.SetMatrix(4, 1, 5);
  test.SetMatrix(4, 2, 5);
  test.SetMatrix(4, 3, 5);
  test.SetMatrix(4, 4, 5);
  double b[25] = {-5, 5, 0, 0, 0, 5, -10, 5, 0, 0, 0, 5, -10, 5, 0, 0, 0, 5, -10, 5, 0, 0, 0, 5, -4};
  test1 = test.CalcComplements();
  int a = 1;
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      if (test1.GetMatrix(i, j) != b[test1.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operation_test, inverse_matrix) {
  S21Matrix test(5, 5);
  S21Matrix test1(5, 5);
  test.SetMatrix(0, 0, 1);
  test.SetMatrix(0, 1, 2);
  test.SetMatrix(0, 2, 3);
  test.SetMatrix(0, 3, 4);
  test.SetMatrix(0, 4, 5);
  test.SetMatrix(1, 0, 2);
  test.SetMatrix(1, 1, 2);
  test.SetMatrix(1, 2, 3);
  test.SetMatrix(1, 3, 4);
  test.SetMatrix(1, 4, 5);
  test.SetMatrix(2, 0, 3);
  test.SetMatrix(2, 1, 3);
  test.SetMatrix(2, 2, 3);
  test.SetMatrix(2, 3, 4);
  test.SetMatrix(2, 4, 5);
  test.SetMatrix(3, 0, 4);
  test.SetMatrix(3, 1, 4);
  test.SetMatrix(3, 2, 4);
  test.SetMatrix(3, 3, 4);
  test.SetMatrix(3, 4, 5);
  test.SetMatrix(4, 0, 5);
  test.SetMatrix(4, 1, 5);
  test.SetMatrix(4, 2, 5);
  test.SetMatrix(4, 3, 5);
  test.SetMatrix(4, 4, 5);
  double b[25] = {-1, 1, 0, 0, 0, 1, -2, 1, 0, 0, 0, 1, -2, 1, 0, 0, 0, 1, -2, 1, 0, 0, 0, 1, -0.8};
  test1 = test.InverseMatrix();
  int a = 1;
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      if (test1.GetMatrix(i, j) != b[test1.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, sum_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  S21Matrix tmp(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      tmp.SetMatrix(i, j, 2 * i);
    }
  }
  S21Matrix test2(test + test1);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test2.GetMatrix(i, j) != tmp.GetMatrix(i, j)) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, copy_constructor) {
  S21Matrix test(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  S21Matrix test1 = test;
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test1.GetMatrix(i, j) != test.GetMatrix(i, j)) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, move_constructor) {
  S21Matrix test(5, 4);
  S21Matrix tmp(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      tmp.SetMatrix(i, j, i);
    }
  }
  S21Matrix test1 = std::move(test);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test1.GetMatrix(i, j) != i) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, index_operation) {
  S21Matrix test(5, 4);
  test.SetMatrix(1, 1, 5);
  EXPECT_TRUE(test(1, 1) == 5);
}

TEST(operator_test, sum_and_eq_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  S21Matrix tmp(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      tmp.SetMatrix(i, j, 2 * i);
    }
  }
  test += test1;
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test.GetMatrix(i, j) != tmp.GetMatrix(i, j)) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, sub_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  S21Matrix test2(test - test1);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test2.GetMatrix(i, j) != 0) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, sub_and_eq_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  test -= test1;
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test.GetMatrix(i, j) != 0) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, eq_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  EXPECT_TRUE(test == test1);
}

TEST(operator_test, mul_and_eq_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(4, 5);
  double b[25] = {0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 18, 18, 18, 18, 18, 24, 24, 24, 24, 24};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  test *= test1;
  int a = 1;
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      if (test.GetMatrix(i, j) != b[test.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, mul_eq_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(4, 5);
  double b[25] = {0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 18, 18, 18, 18, 18, 24, 24, 24, 24, 24};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  test *= test1;
  int a = 1;
  for (int i = 0; i < test.GetRows(); i++) {
    for (int j = 0; j < test.GetCols(); j++) {
      if (test.GetMatrix(i, j) != b[test.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, mul_num_eq_matrix) {
  S21Matrix test(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  test *= -1;
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test.GetMatrix(i, j) != i * -1) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, mul_num_matrix_left) {
  S21Matrix test(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  S21Matrix test1(test * -1);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test1.GetMatrix(i, j) != i * -1) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, mul_num_matrix_right) {
  S21Matrix test(5, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  S21Matrix test1(-1 * test);
  int a = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (test1.GetMatrix(i, j) != i * -1) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, mul_matrix) {
  S21Matrix test(5, 4);
  S21Matrix test1(4, 5);
  double b[25] = {0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 18, 18, 18, 18, 18, 24, 24, 24, 24, 24};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      test.SetMatrix(i, j, i);
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      test1.SetMatrix(i, j, i);
    }
  }
  S21Matrix test2(test * test1);
  int a = 1;
  for (int i = 0; i < test2.GetRows(); i++) {
    for (int j = 0; j < test2.GetCols(); j++) {
      if (test2.GetMatrix(i, j) != b[test2.GetCols() * i + j]) {
        a = 0;
      }
    }
  }
  EXPECT_TRUE(a == 1);
}

TEST(operator_test, const_index_operation) {
  const S21Matrix test(5, 4);
  EXPECT_TRUE(test(1, 1) == 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}