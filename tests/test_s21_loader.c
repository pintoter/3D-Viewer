#include "test.h"

START_TEST(s21_loader_test_1) {
  object_t obj;
  int code = 0;

  code = s21_loader("./../datasets/file_not_found.obj", &obj);

  ck_assert_int_eq(code, FILE_NOT_FOUND);
}
END_TEST

START_TEST(s21_loader_test_2) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/empty_file.obj", "w");
  if (fp != NULL) fclose(fp);

  code = s21_loader("./../datasets/empty_file.obj", &obj);
  ck_assert_int_eq(code, EMPTY_FILE);
}
END_TEST

START_TEST(s21_loader_test_3) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/null_vertexes.obj", "w");
  if (fp != NULL) {
    fprintf(fp, "This project created by leaflaur, harmondp, pintoter\n");
    fclose(fp);
  }

  code = s21_loader("./../datasets/null_vertexes.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

START_TEST(s21_loader_test_4) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/uncorrect_v.obj", "w");
  if (fp != NULL) {
    fprintf(fp, "v 1 2");
    fclose(fp);
  }

  code = s21_loader("./../datasets/uncorrect_v.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

START_TEST(s21_loader_test_5) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/uncorrect_f_1.obj", "w");
  if (fp != NULL) {
    fprintf(fp, "f 1 2");
    fclose(fp);
  }

  code = s21_loader("./../datasets/uncorrect_f_1.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

START_TEST(s21_loader_test_6) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/uncorrect_f_2.obj", "w");
  if (fp != NULL) {
    fprintf(fp, "f 1 2 -3");
    fclose(fp);
  }

  code = s21_loader("./../datasets/uncorrect_f_2.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

START_TEST(s21_loader_test_7) {
  object_t obj;
  int code = 0;

  code = s21_loader("./../datasets/pyramid.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

START_TEST(s21_loader_test_8) {
  object_t obj;
  int code = 0, i = 0, j = 0;

  int expected_polygon_count_vertex[] = {3, 3, 3, 3, 3, 3};
  int expected_polygon_vertex_list[][3] = {{1, 2, 3}, {1, 3, 4}, {1, 4, 5},
                                           {1, 5, 2}, {3, 2, 4}, {2, 5, 4}};
  double expected_matrix[][3] = {{0.0, 1.0, 0.0},
                                 {-1.0, 0.0, -1.0},
                                 {1.0, 0.0, -1.0},
                                 {1.0, 0.0, 1.0},
                                 {-1.0, 0.0, 1.0}};
  int expected_count_vertexes = 5;
  int expected_count_facets = 6;
  char expected_name[] = "correct_pyramid.obj";

  code = s21_loader("./../datasets/correct_pyramid.obj", &obj);

  ck_assert_int_eq(code, CORRECT);
  ck_assert_int_eq(expected_count_vertexes, obj.count_vertexes);
  ck_assert_int_eq(expected_count_facets, obj.count_facets);
  ck_assert_str_eq(expected_name, obj.name);
  for (i = 0; i < obj.count_vertexes; i++) {
    for (j = 0; j < 3; j++)
      ck_assert(fabs(obj.matrix.matrix[i][j] - expected_matrix[i][j]) <
                PRECISION);
  }
  for (i = 0; i < obj.count_facets; i++) {
    ck_assert_int_eq(expected_polygon_count_vertex[i],
                     obj.polygon[i].count_vertex_of_facets);
    for (j = 0; j < obj.polygon[i].count_vertex_of_facets; j++) {
      ck_assert_int_eq(obj.polygon[i].vertexes_list[j],
                       expected_polygon_vertex_list[i][j]);
    }
  }

  s21_remove_object(&obj);
}
END_TEST

START_TEST(s21_loader_test_9) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/uncorrect_f_3.obj", "w");
  if (fp != NULL) {
    fprintf(fp, "fabcd");
    fclose(fp);
  }

  code = s21_loader("./../datasets/uncorrect_f_3.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

START_TEST(s21_loader_test_10) {
  object_t obj;
  int code = 0;

  FILE *fp = fopen("./../datasets/uncorrect_f_3.obj", "w");
  if (fp != NULL) {
    fprintf(fp, "v 1 2 3\nf 1 2 3");
    fclose(fp);
  }

  code = s21_loader("./../datasets/uncorrect_f_3.obj", &obj);
  ck_assert_int_eq(code, UNCORRECT);
}
END_TEST

Suite *test_s21_loader(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_loader_test");
  tc = tcase_create("s21_loader_tc");

  tcase_add_test(tc, s21_loader_test_1);
  tcase_add_test(tc, s21_loader_test_2);
  tcase_add_test(tc, s21_loader_test_3);
  tcase_add_test(tc, s21_loader_test_4);
  tcase_add_test(tc, s21_loader_test_5);
  tcase_add_test(tc, s21_loader_test_6);
  tcase_add_test(tc, s21_loader_test_7);
  tcase_add_test(tc, s21_loader_test_8);
  tcase_add_test(tc, s21_loader_test_9);
  tcase_add_test(tc, s21_loader_test_10);

  suite_add_tcase(s, tc);

  return s;
}
