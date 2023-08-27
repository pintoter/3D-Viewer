#include "include/s21_3DViewer_v1.h"

void s21_geometric_rotations(object_t *data) {
  if (data != NULL) {
    centering_object(data);

    if (!is_displayable(data)) reduction_object(data);
  }
}

void centering_object(object_t *data) {
  if (data != NULL) {
    double x_avg = 0, y_avg = 0, z_avg = 0;

    x_avg = find_geometric_center(data, Ox);
    if (fabs(x_avg) > PRECISION) rotate_object(data, Ox, x_avg);

    y_avg = find_geometric_center(data, Oy);
    if (fabs(y_avg) > PRECISION) rotate_object(data, Oy, y_avg);

    z_avg = find_geometric_center(data, Oz);
    if (fabs(z_avg) > PRECISION) rotate_object(data, Oz, z_avg);
  }
}

double find_geometric_center(object_t *data, int axis) {
  double res = 0;
  if (data != NULL) {
    for (int i = 0; i < data->count_vertexes; i++) {
      res += data->matrix.matrix[i][axis];
    }

    res /= (data->count_vertexes);
  }
  return res;
}

void rotate_object(object_t *data, int axis, double axis_coordinate) {
  if (data != NULL) {
    for (int i = 0; i < data->count_vertexes; i++) {
      data->matrix.matrix[i][axis] -= axis_coordinate;
    }
  }
}

int is_displayable(object_t *data) {
  int flag = 0;
  if (data != NULL) {
    data->max_value_coordinate = data->matrix.matrix[0][0];
    for (int i = 0; i < data->count_vertexes; i++) {
      for (int j = 0; j < Oxyz; j++) {
        if (data->matrix.matrix[i][j] > data->max_value_coordinate) {
          data->max_value_coordinate = data->matrix.matrix[i][j];
        }

        if (fabs(data->matrix.matrix[i][j]) > 1) {
          flag = 1;
        }
      }
    }
  }

  return flag == 0;
}

void reduction_object(object_t *data) {
  double scaler = 0;
  if (data != NULL) {
    scaler = data->max_value_coordinate * 2;

    for (int i = 0; i < data->count_vertexes; i++) {
      for (int j = 0; j < Oxyz; j++) {
        data->matrix.matrix[i][j] /= scaler;
      }
    }
  }
}
