//  Copyright 2022 jewfishc
#include "s21_test.h"

START_TEST(create) {
  matrix_t matrix;
  ck_assert_int_eq(0, s21_create_matrix(3, 3, &matrix));
  ck_assert_int_eq(3, matrix.rows);
  ck_assert_int_eq(3, matrix.columns);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) ck_assert_int_eq(0, matrix.matrix[i][j]);
  }
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(fail_create) {
  matrix_t *matrix = NULL;
  ck_assert_int_eq(1, s21_create_matrix(3, 0, matrix));
  ck_assert_int_eq(1, s21_create_matrix(0, 1, matrix));
  ck_assert_int_eq(1, s21_create_matrix(0, 0, matrix));
}
END_TEST

START_TEST(equal) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  ck_assert_int_eq(matrix_1.columns, matrix_2.columns);
  ck_assert_int_eq(matrix_1.rows, matrix_2.rows);
  ck_assert_int_eq(1, s21_eq_matrix(&matrix_1, &matrix_2));
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(fail_equal) {
  int rows = rand() % 1000 + 1;
  int columns = rand() % 1000 + 1;
  double value = (rand() - test[_i]) / (rand() + 1);
  matrix_t val1 = {0}, val2 = {0};
  s21_create_matrix(rows, columns, &val1);
  s21_create_matrix(rows, columns, &val2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      val1.matrix[i][j] = value;
      value += (rand() - test[_i]) / (rand() + 1);
      val2.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&val1, &val2), FAILURE);
  s21_remove_matrix(&val1);
  s21_remove_matrix(&val2);
}
END_TEST

START_TEST(transpose) {
  matrix_t matrix_1, res;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &res);
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = mtr_3x3[i][j];
    }
  }
  ck_assert_int_eq(0, s21_transpose(&matrix_1, &res));
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq_tol(matrix_1.matrix[i][j], res.matrix[j][i], 1e-7);
    }
  }
  s21_remove_matrix(&res);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(sum) {
  matrix_t matrix_1, matrix_2, res;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  s21_create_matrix(3, 3, &res);

  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = mtr_3x3[i][j];
      matrix_2.matrix[i][j] = mtr_3x3[i][j];
    }
  }
  ck_assert_int_eq(0, s21_sum_matrix(&matrix_1, &matrix_2, &res));
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq(res.matrix[i][j], matrix_1.matrix[i][j] * 2);
    }
  }
  s21_remove_matrix(&res);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(fail_sum) {
  int rows = rand() % 1000 + 1;
  int columns = rand() % 1000 + 1;
  matrix_t val1 = {0}, val2 = {0}, result = {0};
  s21_create_matrix(rows, columns, &val1);
  rows = rand() % 1000 + 1;
  columns = rand() % 1000 + 1;
  s21_create_matrix(rows, columns, &val2);
  ck_assert_int_eq(s21_sum_matrix(&val1, &val2, &result), CALC_FAIL);
  s21_remove_matrix(&val1);
  s21_remove_matrix(&val2);
}
END_TEST

START_TEST(sub) {
  matrix_t matrix_1, matrix_2, res;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  s21_create_matrix(3, 3, &res);

  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = mtr_3x3[i][j];
      matrix_2.matrix[i][j] = mtr_3x3[i][j];
    }
  }
  ck_assert_int_eq(0, s21_sub_matrix(&matrix_1, &matrix_2, &res));
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq(res.matrix[i][j], 0.0);
    }
  }
  s21_remove_matrix(&res);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(fail_sub) {
  int rows = rand() % 1000 + 1;
  int columns = rand() % 1000 + 1;
  matrix_t val1 = {0}, val2 = {0}, result = {0};
  s21_create_matrix(rows, columns, &val1);
  rows = rand() % 1000 + 1;
  columns = rand() % 1000 + 1;
  s21_create_matrix(rows, columns, &val2);
  ck_assert_int_eq(s21_sub_matrix(&val1, &val2, &result), CALC_FAIL);
  s21_remove_matrix(&val1);
  s21_remove_matrix(&val2);
}
END_TEST

START_TEST(mul_num) {
  matrix_t matrix_1, res;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &res);
  double number = 3.69;
  static const double result[3][3] = {
      {0.5535, 0, -13.4316},
      {31.4757, -15.247449, 455.0508},
      {0, 46.125, -289.00449},
  };
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = mtr_3x3[i][j];
    }
  }
  ck_assert_int_eq(0, s21_mult_number(&matrix_1, number, &res));
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq_tol(res.matrix[i][j], result[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&res);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(mul_mtr) {
  matrix_t matrix_1, matrix_2, res;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &res);
  s21_create_matrix(3, 3, &matrix_2);
  static const double mtr_3x32[3][3] = {
      {0.5535, 0, -13.4316},
      {31.4757, -15.247449, 455.0508},
      {0, 46.125, -289.00449},
  };
  static const double const_result[3][3] = {
      {0.083025, -167.895, 1049.9616036},
      {-125.33938497, 5751.1389840129, -37634.92066548},
      {393.44625, -3803.1492375, 28323.25566129},
  };
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = mtr_3x3[i][j];
      matrix_2.matrix[i][j] = mtr_3x32[i][j];
    }
  }
  ck_assert_int_eq(0, s21_mult_matrix(&matrix_1, &matrix_2, &res));
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq_tol(res.matrix[i][j], const_result[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&res);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(fail_mul_mtr) {
  int rows = rand() % 1000 + 1;
  int columns = rand() % 1000 + 1;
  matrix_t val1 = {0}, val2 = {0}, result = {0};
  s21_create_matrix(rows, columns, &val1);
  rows = rand() % 1000 + 1;
  columns = rand() % 1000 + 1;
  s21_create_matrix(rows, columns, &val2);
  ck_assert_int_eq(s21_mult_matrix(&val1, &val2, &result), CALC_FAIL);
  s21_remove_matrix(&val1);
  s21_remove_matrix(&val2);
}
END_TEST

START_TEST(inverse) {
  matrix_t val1 = {0}, result = {0}, expected = {0};
  int size = 3;
  s21_create_matrix(size, size, &val1);
  s21_create_matrix(size, size, &expected);

  val1.matrix[0][0] = 3;
  val1.matrix[0][1] = 27;
  val1.matrix[0][2] = 18;
  val1.matrix[1][0] = 0;
  val1.matrix[1][1] = 18;
  val1.matrix[1][2] = 15;
  val1.matrix[2][0] = 24;
  val1.matrix[2][1] = 9;
  val1.matrix[2][2] = 9;

  expected.matrix[0][0] = 0.01333333333;
  expected.matrix[0][1] = -0.04;
  expected.matrix[0][2] = 0.04;
  expected.matrix[1][0] = 0.1777777778;
  expected.matrix[1][1] = -0.2;
  expected.matrix[1][2] = -0.02222222222;
  expected.matrix[2][0] = -0.2133333333;
  expected.matrix[2][1] = 0.3066666667;
  expected.matrix[2][2] = 0.02666666667;

  ck_assert_int_eq(s21_inverse_matrix(&val1, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&val1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(fail_inverse) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, MATRIX_FAIL);
}
END_TEST

START_TEST(fail_inverse_2) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALC_FAIL);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(det) {
  int size = 5;
  matrix_t val1 = {0};
  s21_create_matrix(size, size, &val1);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) val1.matrix[i][j] = j;
  double result = 0;
  ck_assert_int_eq(s21_determinant(&val1, &result), OK);
  ck_assert_double_eq_tol(result, 0, 1e-6);
  s21_remove_matrix(&val1);
}
END_TEST

START_TEST(complements) {
  matrix_t a = {0};
  s21_create_matrix(3, 3, &a);
  matrix_t result = {0};
  s21_create_matrix(3, 3, &result);
  matrix_t m;
  result.matrix[0][0] = 0;
  result.matrix[0][1] = 10;
  result.matrix[0][2] = -20;
  result.matrix[1][0] = 4;
  result.matrix[1][1] = -14;
  result.matrix[1][2] = 8;
  result.matrix[2][0] = -8;
  result.matrix[2][1] = -2;
  result.matrix[2][2] = 4;

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  s21_calc_complements(&a, &m);
  ck_assert_int_eq(s21_eq_matrix(&result, &m), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(fail_complements) {
  matrix_t A = {0};
  matrix_t B = {0};
  ck_assert_int_eq(s21_calc_complements(&A, &B), MATRIX_FAIL);
}
END_TEST

START_TEST(fail_complements_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 2, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &B), CALC_FAIL);
  s21_remove_matrix(&A);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("Lib_matrix");
  TCase *tc1 = tcase_create("Matrix Operators");
  SRunner *runner = srunner_create(suite);
  int nf;
  puts("\e[4; 46; 33m");

  suite_add_tcase(suite, tc1);
  tcase_add_test(tc1, create);
  tcase_add_test(tc1, fail_create);
  tcase_add_test(tc1, equal);
  tcase_add_test(tc1, fail_equal);
  tcase_add_test(tc1, transpose);
  tcase_add_test(tc1, sum);
  tcase_add_test(tc1, fail_sum);
  tcase_add_test(tc1, sub);
  tcase_add_test(tc1, fail_sub);
  tcase_add_test(tc1, mul_num);
  tcase_add_test(tc1, mul_mtr);
  tcase_add_test(tc1, fail_mul_mtr);
  tcase_add_test(tc1, inverse);
  tcase_add_test(tc1, fail_inverse);
  tcase_add_test(tc1, fail_inverse_2);
  tcase_add_test(tc1, det);
  tcase_add_test(tc1, complements);
  tcase_add_test(tc1, fail_complements);
  tcase_add_test(tc1, fail_complements_2);

  srunner_run_all(runner, CK_ENV);
  nf = srunner_ntests_failed(runner);
  srunner_free(runner);
  return nf == 0 ? 0 : 1;
}
