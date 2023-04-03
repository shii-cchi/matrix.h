#include "_matrix.h"

int _create_matrix(int rows, int columns, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (rows >= 1 && columns >= 1 && (int)rows == rows &&
      (int)columns == columns) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          break;
        }
      }
      result->rows = rows;
      result->columns = columns;
      status = OK;
    }
  }
  return status;
}

void _remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

int _eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs((A->matrix[i][j] - B->matrix[i][j])) > EPS) {
          status = FAILURE;
          break;
        }
      }
    }
  } else {
    status = FAILURE;
  }
  return status;
}

int _sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status;
  status = _sum_sub_matrix(A, B, result, 1);
  return status;
}

int _sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status;
  status = _sum_sub_matrix(A, B, result, 2);
  return status;
}

int _sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int operation) {
  int status = INCORRECT_MATRIX;
  if (A->rows == B->rows && A->columns == B->columns) {
    if (_create_matrix(A->rows, A->columns, result) != INCORRECT_MATRIX) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          int n = -1;
          if (operation == 1) {
            n = 1;
          }
          result->matrix[i][j] = A->matrix[i][j] + n * B->matrix[i][j];
        }
      }
      status = OK;
    }
  } else {
    status = CALCULATION_ERROR;
  }
  return status;
}

int _mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (_create_matrix(A->rows, A->columns, result) != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    status = OK;
  }
  return status;
}

int _mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A->columns == B->rows) {
    if (_create_matrix(A->rows, B->columns, result) != INCORRECT_MATRIX) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
      status = OK;
    }
  } else {
    status = CALCULATION_ERROR;
  }
  return status;
}

int _transpose(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (_create_matrix(A->columns, A->rows, result) != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
    status = OK;
  }
  return status;
}

int _calc_complements(matrix_t *A, matrix_t *result) {
  int status = INCORRECT_MATRIX;
  if (A->rows == A->columns && A->rows >= 2) {
    if (_create_matrix(A->columns, A->rows, result) != INCORRECT_MATRIX) {
      matrix_t new_A;
      _create_matrix(A->rows - 1, A->columns - 1, &new_A);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          _clear_matrix(&new_A);
          _matrix_without_row_column(A, &new_A, i, j);
          double minor;
          _determinant(&new_A, &minor);
          result->matrix[i][j] = minor * pow(-1, i + j);
        }
      }
      _remove_matrix(&new_A);
      status = OK;
    }
  } else {
    status = CALCULATION_ERROR;
  }
  return status;
}

void _matrix_without_row_column(matrix_t *A, matrix_t *new_A, int row,
                                int column) {
  int n = 0;
  for (int i = 0; i < new_A->rows; i++) {
    int m = 0;
    if (i == row) {
      n = 1;
    }
    for (int j = 0; j < new_A->columns; j++) {
      if (j == column) {
        m = 1;
      }
      new_A->matrix[i][j] = A->matrix[i + n][j + m];
    }
  }
}

void _clear_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = 0;
    }
  }
}

int _determinant(matrix_t *A, double *result) {
  int status = INCORRECT_MATRIX;
  if (A->rows == A->columns) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
      status = OK;
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      status = OK;
    } else {
      matrix_t new_A;
      if (_create_matrix(A->rows - 1, A->columns - 1, &new_A) !=
          INCORRECT_MATRIX) {
        double minor = 0;
        for (int j = 0; j < A->columns; j++) {
          int i = 0;
          _clear_matrix(&new_A);
          _matrix_without_row_column(A, &new_A, i, j);
          _determinant(&new_A, result);
          *result *= A->matrix[i][j] * pow((-1), i + j);
          minor += *result;
        }
        *result = minor;
        _remove_matrix(&new_A);
        status = OK;
      }
    }
  } else {
    status = CALCULATION_ERROR;
  }
  return status;
}

int _inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A->rows == A->columns) {
    double determinant;
    _determinant(A, &determinant);
    if (determinant != 0) {
      matrix_t minors, trans;
      _calc_complements(A, &minors);
      _transpose(&minors, &trans);
      _mult_number(&trans, 1 / determinant, result);
      _remove_matrix(&minors);
      _remove_matrix(&trans);
    } else {
      status = CALCULATION_ERROR;
    }
  } else {
    status = CALCULATION_ERROR;
  }
  return status;
}
