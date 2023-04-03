#ifndef SRC__MATRIX_H_
#define SRC__MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define SUCCESS 1
#define FAILURE 2

#define EPS 1e-8

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int _create_matrix(int rows, int columns, matrix_t *result);
void _remove_matrix(matrix_t *A);
int _eq_matrix(matrix_t *A, matrix_t *B);
int _sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int _sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int _mult_number(matrix_t *A, double number, matrix_t *result);
int _mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int _transpose(matrix_t *A, matrix_t *result);
int _calc_complements(matrix_t *A, matrix_t *result);
int _determinant(matrix_t *A, double *result);
int _inverse_matrix(matrix_t *A, matrix_t *result);

int _sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int operation);
void _matrix_without_row_column(matrix_t *A, matrix_t *new_A, int row,
                                int column);
void _clear_matrix(matrix_t *A);

#endif  //  SRC__MATRIX_H_
