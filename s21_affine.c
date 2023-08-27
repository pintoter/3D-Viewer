#include "include/s21_3DViewer_v1.h"

void s21_move_x(object_t *data, double move_x) {
  if (data != NULL) {
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      data->matrix.matrix[i][Ox] += move_x;
    }
  }
}

void s21_move_y(object_t *data, double move_y) {
  if (data != NULL) {
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      data->matrix.matrix[i][Oy] += move_y;
    }
  }
}

void s21_move_z(object_t *data, double move_z) {
  if (data != NULL) {
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      data->matrix.matrix[i][Oz] += move_z;
    }
  }
}

double s21_degres_to_radians(double angle) { return angle * M_PI / 180.0; }

void s21_rotate_x(object_t *data, double angle) {
  if (angle > PRECISION && data != NULL) {
    angle = s21_degres_to_radians(angle);
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      double y = data->matrix.matrix[i][Oy];
      double z = data->matrix.matrix[i][Oz];

      data->matrix.matrix[i][Oy] = y * cosl(angle) + z * sinl(angle);
      data->matrix.matrix[i][Oz] = -y * sinl(angle) + z * cosl(angle);
    }
  }
}

void s21_rotate_y(object_t *data, double angle) {
  if (angle > PRECISION && data != NULL) {
    angle = s21_degres_to_radians(angle);
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      double x = data->matrix.matrix[i][Ox];
      double z = data->matrix.matrix[i][Oz];

      data->matrix.matrix[i][Ox] = x * cosl(angle) + z * sinl(angle);
      data->matrix.matrix[i][Oz] = -x * sinl(angle) + z * cosl(angle);
    }
  }
}

void s21_rotate_z(object_t *data, double angle) {
  if (angle > PRECISION && data != NULL) {
    angle = s21_degres_to_radians(angle);
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      double x = data->matrix.matrix[i][Ox];
      double y = data->matrix.matrix[i][Oy];

      data->matrix.matrix[i][Ox] = x * cosl(angle) - y * sinl(angle);
      data->matrix.matrix[i][Oy] = x * sinl(angle) + y * cosl(angle);
    }
  }
}

void s21_scale(object_t *data, double scale, double prev_scale) {
  if (scale > PRECISION && prev_scale > PRECISION && data != NULL) {
    for (int i = 0; data->matrix.matrix && i < data->count_vertexes; i++) {
      for (int j = 0; j < Oxyz; j++) {
        data->matrix.matrix[i][j] *= scale / prev_scale;
      }
    }
  }
}
