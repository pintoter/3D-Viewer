#include "test.h"

START_TEST(s21_affine_move_x_test) {
  object_t obj;
  double expected_matrix[][3] = {{1.0, 1.0, 0.0},
                                 {0.0, 0.0, -1.0},
                                 {2.0, 0.0, -1.0},
                                 {2.0, 0.0, 1.0},
                                 {0.0, 0.0, 1.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);
  s21_move_x(&obj, 1.0);

  ck_assert_int_eq(code, CORRECT);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++)
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_affine_move_y_test) {
  object_t obj;
  double expected_matrix[][3] = {{0.0, 2.0, 0.0},
                                 {-1.0, 1.0, -1.0},
                                 {1.0, 1.0, -1.0},
                                 {1.0, 1.0, 1.0},
                                 {-1.0, 1.0, 1.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);
  s21_move_y(&obj, 1.0);

  ck_assert_int_eq(code, CORRECT);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++) {
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
    }
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_affine_move_z_test) {
  object_t obj;
  double expected_matrix[][3] = {{0.0, 1.0, 1.0},
                                 {-1.0, 0.0, 0.0},
                                 {1.0, 0.0, 0.0},
                                 {1.0, 0.0, 2.0},
                                 {-1.0, 0.0, 2.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);
  s21_move_z(&obj, 1.0);

  ck_assert_int_eq(code, CORRECT);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++)
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_degres_to_radians_test) {
  double expected_radians = 0.0174533;

  ck_assert(fabs(s21_degres_to_radians(1) - expected_radians) < PRECISION);
}
END_TEST

START_TEST(s21_rotate_x_test) {
  object_t obj;
  double expected_matrix[][3] = {{0.0, 0.0, -1.0},
                                 {-1.0, -1.0, 0.0},
                                 {1.0, -1.0, 0.0},
                                 {1.0, 1.0, 0.0},
                                 {-1.0, 1.0, 0.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);
  s21_rotate_x(&obj, 90);

  ck_assert_int_eq(code, CORRECT);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++) {
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
    }
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_rotate_y_test) {
  object_t obj;
  double expected_matrix[][3] = {{0.0, 1.0, 0.0},
                                 {-1.0, 0.0, 1.0},
                                 {-1.0, 0.0, -1.0},
                                 {1.0, 0.0, -1.0},
                                 {1.0, 0.0, 1.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);
  s21_rotate_y(&obj, 90);

  ck_assert_int_eq(code, CORRECT);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++) {
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
    }
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_rotate_z_test) {
  object_t obj;
  double expected_matrix[][3] = {{-1.0, 0.0, 0.0},
                                 {0.0, -1.0, -1.0},
                                 {0.0, 1.0, -1.0},
                                 {0.0, 1.0, 1.0},
                                 {0.0, -1.0, 1.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);
  s21_rotate_z(&obj, 90);

  ck_assert_int_eq(code, CORRECT);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++) {
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
    }
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_scale_test) {
  object_t obj;
  double expected_matrix[][3] = {{0.0, 2.0, 0.0},
                                 {-2.0, 0.0, -2.0},
                                 {2.0, 0.0, -2.0},
                                 {2.0, 0.0, 2.0},
                                 {-2.0, 0.0, 2.0}};
  int code = 0, i = 0, j = 0;

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);

  ck_assert_int_eq(code, CORRECT);

  s21_scale(&obj, 2, 1);

  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++)
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
  }

  s21_remove_object(&obj);
}
END_TEST

Suite* test_s21_affine(void) {
  Suite* s;
  TCase* tc;

  s = suite_create("s21_affine_test");
  tc = tcase_create("s21_affine_tc");

  tcase_add_test(tc, s21_affine_move_x_test);
  tcase_add_test(tc, s21_affine_move_y_test);
  tcase_add_test(tc, s21_affine_move_z_test);
  tcase_add_test(tc, s21_degres_to_radians_test);
  tcase_add_test(tc, s21_rotate_x_test);
  tcase_add_test(tc, s21_rotate_y_test);
  tcase_add_test(tc, s21_rotate_z_test);
  tcase_add_test(tc, s21_scale_test);

  suite_add_tcase(s, tc);

  return s;
}