//  Copyright 2022 jewfishc
#include "s21_matrix.h"

//  Создает матрицу
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix) {
      res = s21_allocate(result);
    } else {
      res = MATRIX_FAIL;
    }
  } else {
    res = MATRIX_FAIL;
  }

  return res;
}

//  Выделяет память
int s21_allocate(matrix_t *result) {
  int res = OK;
  for (int i = 0; i < result->rows && res == OK; i++) {
    result->matrix[i] = calloc(result->columns, sizeof(double));
    if (result->matrix[i]) {
      for (int js = 0; js < result->columns; js++) {
        result->matrix[i][js] = 0;
      }
    } else {
      res = MATRIX_FAIL;
      s21_remove_matrix(result);
    }
  }
  return res;
}

//  Удаляет и очищает память
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
  }
}

//  Сравнивает матрицы
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (s21_mtrcmp(*A, *B) == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double accuracy = A->matrix[i][j] - B->matrix[i][j];
        if (fabs(accuracy) > EPS) res = FAILURE;
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

//  Проверяет матрицы на существование
int s21_mtr_check(matrix_t A) {
  int res = OK;
  if (A.matrix) {
    if (A.columns < 1 || A.rows < 1) {
      res = MATRIX_FAIL;
    }
  } else {
    res = MATRIX_FAIL;
  }
  return res;
}

//  Проверяет равенство столбцов и строк
int s21_mtrcmp(matrix_t A, matrix_t B) {
  int res = s21_mtr_check(A);
  if (res == OK) res = s21_mtr_check(B);
  if (res == OK) {
    if ((A.rows != B.rows || A.columns != B.columns)) res = CALC_FAIL;
  }
  return res;
}

//  Складывает матрицы
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = s21_mtrcmp(*A, *B);
  if (res == OK) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

//  Вычитает матрицы
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = s21_mtrcmp(*A, *B);
  if (res == OK) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

//  Умножает матрицу на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (number != number) {
    res = CALC_FAIL;
  } else if ((res = s21_mtr_check(*A)) == OK) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return res;
}

//  Умножает матрицы
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = s21_mtr_check(*A);
  if (res == OK) s21_mtr_check(*B);
  if (res == OK) {
    if (A->columns == B->rows) {
      res = s21_create_matrix(A->rows, B->columns, result);
      if (res == OK) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      res = CALC_FAIL;
    }
  }
  return res;
}

//  Транспонирует матрицу
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = s21_create_matrix(A->columns, A->rows, result);
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

//  Вычисляет миноры и алгебраические дополнения матрицы
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = s21_mtr_check(*A);
  if (res == OK) {
    if (A->rows == A->columns) {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == OK) {
        if (A->rows == 1) {
          result->matrix[0][0] = 1;
        } else {
          res = s21_complements_simple(A, result);
        }
      }
    } else {
      res = CALC_FAIL;
    }
  }
  return res;
}

//  Прямое вычисление миноров
int s21_complements_simple(matrix_t *A, matrix_t *result) {
  int res = OK;
  int sign = -1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double determinant = 0.0;
      matrix_t tmp = {0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
      s21_complements(A, &tmp, i, j, A->rows);
      s21_determinant(&tmp, &determinant);
      result->matrix[i][j] = powf(sign, (i + j)) * determinant;
      s21_remove_matrix(&tmp);
    }
  }

  return res;
}

//  Вычисляет определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  int res = s21_mtr_check(*A);
  if (res == OK) {
    if (A->rows == A->columns) {
      *result = s21_det_simple(A, A->rows);
    } else {
      res = CALC_FAIL;
    }
  }
  return res;
}

//  Вычисляет определитель матрицы x2
double s21_det_simple(matrix_t *A, int tmp_rows) {
  double determinant = 0.0;
  if (tmp_rows == 1) {
    determinant = A->matrix[0][0];
  } else {
    int sign = 1;
    matrix_t tmp = {0};
    s21_create_matrix(A->rows, A->columns, &tmp);
    for (int i = 0; i < tmp_rows; i++) {
      s21_complements(A, &tmp, 0, i, tmp_rows);
      determinant +=
          sign * A->matrix[0][i] * s21_det_simple(&tmp, tmp_rows - 1);
      sign = -sign;
    }
    s21_remove_matrix(&tmp);
  }
  return determinant;
}

//  Прямое вычисление алгебраических дополнений
void s21_complements(matrix_t *A, matrix_t *tmp, int tmp_row, int tmp_column,
                     int matrix_rows) {
  int k = 0, l = 0;
  for (int i = 0; i < matrix_rows; i++) {
    for (int j = 0; j < matrix_rows; j++) {
      if (i != tmp_row && j != tmp_column) {
        tmp->matrix[k][l++] = A->matrix[i][j];
        if (l == matrix_rows - 1) {
          l = 0;
          k++;
        }
      }
    }
  }
}

//  Вычисляет обратную матрицу
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  double determinant = 0.0;
  if (A->matrix) {
    res = s21_determinant(A, &determinant);
  } else {
    res = MATRIX_FAIL;
  }
  if (determinant != 0 && res == OK) {
    matrix_t complements = {0};
    res = s21_calc_complements(A, &complements);
    if (res == OK) {
      res = s21_transpose(&complements, result);
      s21_remove_matrix(&complements);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] /= determinant;
          }
        }
      }
    }
  } else if (res == OK) {
    res = CALC_FAIL;
  }
  return res;
}
