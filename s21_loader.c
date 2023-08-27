#include "include/s21_3DViewer_v1.h"

int s21_loader(const char *path, object_t *data) {
  FILE *fp = NULL;
  long size_f = 0;
  data->polygon = NULL;
  data->count_facets = 0;
  data->count_vertexes = 0;
  data->max_value_coordinate = 0;
  data->max_vertex = 0;
  int code = CORRECT;

  // setlocale(LC_ALL, "");
  fp = fopen(path, "r");

  if (fp == NULL) {
    return FILE_NOT_FOUND;
  }

  fseek(fp, 0, SEEK_END);
  size_f = ftell(fp);

  if (!size_f) {
    fclose(fp);
    return EMPTY_FILE;
  }

  fseek(fp, 0, SEEK_SET);
  count_geometric_params(fp, data);

  if (data->count_vertexes == 0) {
    fclose(fp);
    return UNCORRECT;
  }

  fseek(fp, 0, SEEK_SET);
  s21_create_matrix(data->count_vertexes, Oxyz, &(data->matrix));

  if ((code = parse_geometric_params(fp, data)) != CORRECT) {
    fclose(fp);
    s21_remove_object(data);
    return code;
  }

  get_name(path, data);

  fclose(fp);

  return CORRECT;
}

void count_geometric_params(FILE *fp, object_t *data) {
  char str[SIZE] = {0};
  char *p = NULL;
  char ch = 0;

  while (fgets(str, SIZE, fp) != NULL) {
    p = str;

    skip_spaces(&p);

    ch = *p;

    if (ch == 'v' && is_vertex(p))
      (data->count_vertexes)++;
    else if (ch == 'f')
      (data->count_facets)++;
  }
}

int parse_geometric_params(FILE *fp, object_t *data) {
  char str[SIZE] = {0};
  char *p = NULL;
  char ch = 0;
  int cur_vertex = 0, cur_facets = 0, err = CORRECT;

  while (fgets(str, SIZE, fp) != NULL) {
    p = str;

    skip_spaces(&p);

    ch = *p;

    if ((ch == 'v' && is_vertex(p)) || ch == 'f') {
      err = write_value(data, p, ch == 'v' ? &cur_vertex : &cur_facets);

      if (err != CORRECT) {
        data->count_vertexes = cur_vertex;
        data->count_facets = cur_facets + 1;
        s21_remove_object(data);
        return err;
      }
    }
  }

  if (data->max_vertex > data->count_vertexes) {
    return UNCORRECT;
  }

  return err;
}

int write_value(object_t *data, char *str, int *current) {
  char *temp_str = NULL, *temp = NULL;

  if (*str == ' ') skip_spaces(&str);

  if (*str == 'v' &&
      sscanf(str, "v %lf %lf %lf", &(data->matrix.matrix[*current][0]),
             &(data->matrix.matrix[*current][1]),
             &(data->matrix.matrix[*current][2])) != 3) {
    return UNCORRECT;
  } else if (*str == 'f') {
    str++;

    skip_spaces(&str);

    temp = strtok(str, " ");

    if (temp == NULL) {
      return UNCORRECT;
    }

    if ((data->polygon = (polygon_t *)realloc(
             data->polygon, (*current + 1) * sizeof(polygon_t))) == NULL) {
      return NOT_ENOUGH_MEMORY;
    }

    data->polygon[*current].count_vertex_of_facets = 0;
    data->polygon[*current].vertexes_list = NULL;

    while (temp != NULL) {
      temp_str = temp;

      if ((data->polygon[*current].vertexes_list = (int *)realloc(
               data->polygon[*current].vertexes_list,
               (data->polygon[*current].count_vertex_of_facets + 1) *
                   sizeof(int))) == NULL) {
        return NOT_ENOUGH_MEMORY;
      }

      data->polygon[*current]
          .vertexes_list[data->polygon[*current].count_vertex_of_facets] = 0;

      if (!sscanf(temp_str, "%d",
                  &(data->polygon[*current].vertexes_list
                        [data->polygon[*current].count_vertex_of_facets])) ||
          data->polygon[*current].vertexes_list[data->polygon[*current]
                                                    .count_vertex_of_facets] <=
              0) {
        return UNCORRECT;
      }

      if (data->polygon[*current]
              .vertexes_list[data->polygon[*current].count_vertex_of_facets] >
          data->max_vertex) {
        data->max_vertex =
            data->polygon[*current]
                .vertexes_list[data->polygon[*current].count_vertex_of_facets];
      }

      data->polygon[*current].count_vertex_of_facets += 1;
      temp = strtok(NULL, " ");
    }

    if (data->polygon[*current].count_vertex_of_facets < 3) {
      return UNCORRECT;
    }
  }
  (*current)++;

  return CORRECT;
}

void get_name(const char *path, object_t *data) {
  char *temp;
  temp = strrchr(path, '/');
  temp++;
  strcpy(data->name, temp);
}

void skip_spaces(char **str) {
  while (**str == ' ') (*str)++;
}

int is_vertex(const char *str) {
  str++;
  return *str == ' ';
}