#include "include/s21_3DViewer_v1.h"

void s21_remove_object(object_t *data) {
  if (data != NULL) {
    s21_remove_matrix(&(data->matrix));

    if (data->polygon != NULL) {
      for (int i = 0; i < data->count_facets && data->polygon[i].vertexes_list;
           i++) {
        free(data->polygon[i].vertexes_list);
        data->polygon[i].vertexes_list = NULL;
      }

      free(data->polygon);

      data->polygon = NULL;
    }

    data->count_vertexes = 0;
    data->count_facets = 0;
    data->max_value_coordinate = 0;
    data->max_vertex = 0;
  }
}