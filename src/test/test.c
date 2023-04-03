#include <check.h>

#include "../_matrix.h"

START_TEST(create_and_remove_test_1) {
  matrix_t A;
  ck_assert(_create_matrix(0, 0, &A) == INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_and_remove_test_2) {
  matrix_t A;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert(A.matrix[i][j] == 0);
    }
  }
  _remove_matrix(&A);
}
END_TEST

START_TEST(eq_test) {
  matrix_t A, B, C, D, E;
  ck_assert(_create_matrix(3, 3, &A) == OK);
  ck_assert(_create_matrix(3, 3, &B) == OK);
  ck_assert(_create_matrix(3, 3, &C) == OK);
  ck_assert(_create_matrix(3, 3, &D) == OK);
  ck_assert(_create_matrix(2, 2, &E) == OK);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 1.0000001;
      B.matrix[i][j] = 1.0000001;
      C.matrix[i][j] = 1.0000002;
      D.matrix[i][j] = 2;
    }
  }
  ck_assert(_eq_matrix(&A, &B) == SUCCESS);
  ck_assert(_eq_matrix(&A, &C) == FAILURE);
  ck_assert(_eq_matrix(&A, &D) == FAILURE);
  ck_assert(_eq_matrix(&A, &E) == FAILURE);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&C);
  _remove_matrix(&D);
  _remove_matrix(&E);
}
END_TEST

START_TEST(sum_test_1) {
  matrix_t A, B, C, C1;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  ck_assert(_create_matrix(2, 2, &B) == OK);
  ck_assert(_create_matrix(2, 2, &C1) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;
  C1.matrix[0][0] = 6;
  C1.matrix[0][1] = 8;
  C1.matrix[1][0] = 10;
  C1.matrix[1][1] = 12;
  ck_assert(_sum_matrix(&A, &B, &C) == OK);
  ck_assert(_eq_matrix(&C, &C1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&C);
  _remove_matrix(&C1);
}
END_TEST

START_TEST(sum_test_2) {
  matrix_t A, B, C;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  ck_assert(_create_matrix(3, 3, &B) == OK);
  ck_assert(_sum_matrix(&A, &B, &C) == CALCULATION_ERROR);
  _remove_matrix(&A);
  _remove_matrix(&B);
}
END_TEST

START_TEST(sub_test_1) {
  matrix_t A, B, C, C1;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  ck_assert(_create_matrix(2, 2, &B) == OK);
  ck_assert(_create_matrix(2, 2, &C1) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;
  C1.matrix[0][0] = 4;
  C1.matrix[0][1] = 4;
  C1.matrix[1][0] = 4;
  C1.matrix[1][1] = 4;
  ck_assert(_sub_matrix(&B, &A, &C) == OK);
  ck_assert(_eq_matrix(&C, &C1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&C);
  _remove_matrix(&C1);
}
END_TEST

START_TEST(sub_test_2) {
  matrix_t A, B, C;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  ck_assert(_create_matrix(3, 3, &B) == OK);
  ck_assert(_sum_matrix(&A, &B, &C) == CALCULATION_ERROR);
  _remove_matrix(&A);
  _remove_matrix(&B);
}
END_TEST

START_TEST(mult_number_test) {
  matrix_t A, B, C;
  ck_assert(_create_matrix(3, 3, &A) == OK);
  ck_assert(_create_matrix(3, 3, &B) == OK);
  for (int i = 0; i < A.rows; ++i) {
    for (int j = 0; j < A.columns; ++j) {
      A.matrix[i][j] = 1;
      B.matrix[i][j] = 2;
    }
  }
  ck_assert(_mult_number(&A, 2, &C) == OK);
  ck_assert(_eq_matrix(&B, &C) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&C);
}
END_TEST

START_TEST(mult_matrix_test_1) {
  matrix_t A, B, C, C1;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  ck_assert(_create_matrix(2, 2, &B) == OK);
  ck_assert(_create_matrix(2, 2, &C1) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;
  C1.matrix[0][0] = 19;
  C1.matrix[0][1] = 22;
  C1.matrix[1][0] = 43;
  C1.matrix[1][1] = 50;
  ck_assert(_mult_matrix(&A, &B, &C) == OK);
  ck_assert(_eq_matrix(&C, &C1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&C);
  _remove_matrix(&C1);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t A, B, C;
  ck_assert(_create_matrix(2, 3, &A) == OK);
  ck_assert(_create_matrix(2, 3, &B) == OK);
  ck_assert(_mult_matrix(&A, &B, &C) == CALCULATION_ERROR);
  _remove_matrix(&A);
  _remove_matrix(&B);
}
END_TEST

START_TEST(transpose_test) {
  matrix_t A, B, B1;
  ck_assert(_create_matrix(2, 3, &A) == OK);
  ck_assert(_create_matrix(3, 2, &B1) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  B1.matrix[0][0] = 1;
  B1.matrix[0][1] = 4;
  B1.matrix[1][0] = 2;
  B1.matrix[1][1] = 5;
  B1.matrix[2][0] = 3;
  B1.matrix[2][1] = 6;
  ck_assert(_transpose(&A, &B) == OK);
  ck_assert(_eq_matrix(&B, &B1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&B1);
}
END_TEST

START_TEST(calc_complements_test_1) {
  matrix_t A, B, B1;
  ck_assert(_create_matrix(3, 3, &A) == OK);
  ck_assert(_create_matrix(3, 3, &B1) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  B1.matrix[0][0] = 0;
  B1.matrix[0][1] = 10;
  B1.matrix[0][2] = -20;
  B1.matrix[1][0] = 4;
  B1.matrix[1][1] = -14;
  B1.matrix[1][2] = 8;
  B1.matrix[2][0] = -8;
  B1.matrix[2][1] = -2;
  B1.matrix[2][2] = 4;
  ck_assert(_calc_complements(&A, &B) == OK);
  ck_assert(_eq_matrix(&B, &B1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&B1);
}
END_TEST

START_TEST(calc_complements_test_2) {
  matrix_t A, B;
  ck_assert(_create_matrix(2, 3, &A) == OK);
  ck_assert(_calc_complements(&A, &B) == CALCULATION_ERROR);
  _remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_1) {
  matrix_t A;
  double res_1, res_2;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  res_2 = 0;
  ck_assert(_determinant(&A, &res_1) == OK);
  ck_assert((res_1 == res_2) == SUCCESS);
  _remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t A;
  double res_1, res_2;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  res_2 = 0;
  ck_assert(_determinant(&A, &res_1) == OK);
  ck_assert((res_1 == res_2) == SUCCESS);
  _remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3) {
  matrix_t A;
  double res_1, res_2;
  ck_assert(_create_matrix(3, 3, &A) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  res_2 = 0;
  ck_assert(_determinant(&A, &res_1) == OK);
  ck_assert((res_1 == res_2) == SUCCESS);
  _remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4) {
  matrix_t A;
  double res_1, res_2;
  ck_assert(_create_matrix(3, 3, &A) == OK);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  res_2 = -1;
  ck_assert(_determinant(&A, &res_1) == OK);
  ck_assert((res_1 == res_2) == SUCCESS);
  _remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_5) {
  matrix_t A;
  double res_1, res_2;
  ck_assert(_create_matrix(4, 4, &A) == OK);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 6;
  A.matrix[2][3] = 4;
  A.matrix[3][0] = 4;
  A.matrix[3][1] = 6;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 7;
  res_2 = 75;
  ck_assert(_determinant(&A, &res_1) == OK);
  ck_assert((res_1 == res_2) == SUCCESS);
  _remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_6) {
  matrix_t A;
  double res;
  ck_assert(_create_matrix(2, 3, &A) == OK);
  ck_assert(_determinant(&A, &res) == CALCULATION_ERROR);
  _remove_matrix(&A);
}
END_TEST

START_TEST(inverse_test_1) {
  matrix_t A, B, B1;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  ck_assert(_create_matrix(2, 2, &B1) == OK);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 11;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 2;
  B1.matrix[0][0] = -0.08;
  B1.matrix[0][1] = 0.44;
  B1.matrix[1][0] = 0.12;
  B1.matrix[1][1] = -0.16;
  ck_assert(_inverse_matrix(&A, &B) == OK);
  ck_assert(_eq_matrix(&B, &B1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&B1);
}
END_TEST

START_TEST(inverse_test_2) {
  matrix_t A, B, B1;
  ck_assert(_create_matrix(3, 3, &A) == OK);
  ck_assert(_create_matrix(3, 3, &B1) == OK);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  B1.matrix[0][0] = 1;
  B1.matrix[0][1] = -1;
  B1.matrix[0][2] = 1;
  B1.matrix[1][0] = -38;
  B1.matrix[1][1] = 41;
  B1.matrix[1][2] = -34;
  B1.matrix[2][0] = 27;
  B1.matrix[2][1] = -29;
  B1.matrix[2][2] = 24;
  ck_assert(_inverse_matrix(&A, &B) == OK);
  ck_assert(_eq_matrix(&B, &B1) == SUCCESS);
  _remove_matrix(&A);
  _remove_matrix(&B);
  _remove_matrix(&B1);
}
END_TEST

START_TEST(inverse_test_3) {
  matrix_t A, B;
  ck_assert(_create_matrix(2, 2, &A) == OK);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  ck_assert(_inverse_matrix(&A, &B) == CALCULATION_ERROR);
  _remove_matrix(&A);
}
END_TEST

START_TEST(inverse_test_4) {
  matrix_t A, B;
  ck_assert(_create_matrix(2, 3, &A) == OK);
  ck_assert(_inverse_matrix(&A, &B) == CALCULATION_ERROR);
  _remove_matrix(&A);
}
END_TEST

Suite *_matrix_suite(void) {
  Suite *suite = suite_create("_matrix");
  TCase *tcase_core = tcase_create("matrix");
  tcase_add_test(tcase_core, create_and_remove_test_1);
  tcase_add_test(tcase_core, create_and_remove_test_2);
  tcase_add_test(tcase_core, eq_test);
  tcase_add_test(tcase_core, sum_test_1);
  tcase_add_test(tcase_core, sum_test_2);
  tcase_add_test(tcase_core, sub_test_1);
  tcase_add_test(tcase_core, sub_test_2);
  tcase_add_test(tcase_core, mult_number_test);
  tcase_add_test(tcase_core, mult_matrix_test_1);
  tcase_add_test(tcase_core, mult_matrix_test_2);
  tcase_add_test(tcase_core, transpose_test);
  tcase_add_test(tcase_core, calc_complements_test_1);
  tcase_add_test(tcase_core, calc_complements_test_2);
  tcase_add_test(tcase_core, determinant_test_1);
  tcase_add_test(tcase_core, determinant_test_2);
  tcase_add_test(tcase_core, determinant_test_3);
  tcase_add_test(tcase_core, determinant_test_4);
  tcase_add_test(tcase_core, determinant_test_5);
  tcase_add_test(tcase_core, determinant_test_6);
  tcase_add_test(tcase_core, inverse_test_1);
  tcase_add_test(tcase_core, inverse_test_2);
  tcase_add_test(tcase_core, inverse_test_3);
  tcase_add_test(tcase_core, inverse_test_4);
  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = _matrix_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  srunner_free(suite_runner);
  return 0;
}
