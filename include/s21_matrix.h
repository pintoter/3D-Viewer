#ifndef C6_S21_MATRIX_0_MASTER_MATRIX_H
#define C6_S21_MATRIX_0_MASTER_MATRIX_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define TINY 1.0e-20

#define SUCCESS 1
#define FAILURE 0

#define EQUAL_DIMENSION ((*A).rows == (*B).rows && (*A).columns == (*B).columns)
#define EPS 0.0000001

#define CORRECT_MATRIX 0
#define INCORRECT_MATRIX 1
#define IDENTITY_MATRIX 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

matrix_t s21_get_decMatrix(int rows, int columns, matrix_t *A);
int s21_validMatrix(matrix_t *A);
int s21_isMatrixSquare(matrix_t *A);
void s21_copy_matrix(matrix_t *A, matrix_t *B);
void s21_fill_p_vector(int size, double *det, double **p_vec, matrix_t LUP);
void s21_part_determinant(int *j, int imax, double *d_mul, int size,
                          double *dum, double **p_vec, int **indx,
                          matrix_t *LUP);

#endif  // C6_S21_MATRIX_0_MASTER_MATRIX_H
