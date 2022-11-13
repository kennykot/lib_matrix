//  Copyright 2022 jewfishc
#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define MATRIX_FAIL 1
#define CALC_FAIL 2
#define EPS 1e-07

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int, int, matrix_t *);
void s21_remove_matrix(matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
double s21_det_simple(matrix_t *A, int tmp_rows);
void s21_complements(matrix_t *A, matrix_t *tmp, int tmp_row, int tmp_column,
                     int matrix_rows);
int s21_complements_simple(matrix_t *A, matrix_t *result);
int s21_allocate(matrix_t *result);
int s21_mtrcmp(matrix_t A, matrix_t B);
int s21_mtr_check(matrix_t A);

#endif  // SRC_S21_MATRIX_H_
