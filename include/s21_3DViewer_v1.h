/**
 * \file s21_3DViewer_v1.h
 * \author leaflaur, harmondp, pintoter
 * \brief Описание функций, используемых для обработки данных из файла
 */

#ifndef SRC_INCLUDE_S21_3DVIEWER_V1_H_
#define SRC_INCLUDE_S21_3DVIEWER_V1_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s21_matrix.h"
#include <locale.h>

#define Ox 0 
#define Oy 1
#define Oz 2
#define Oxyz 3
#define SIZE 128
#define PRECISION 1e-7

/**
 * @brief Структура Полигон
 */
typedef struct {
    int *vertexes_list; /**< Список вершин для задания i-ой поверхности */
    int count_vertex_of_facets; /**< Количество вершин для задания i-ой поверхности */
} polygon_t;

/**
 * @brief Структура Объект
 */
typedef struct {
    polygon_t *polygon;  /**< Массив структур Полигон */
    matrix_t matrix; /**< Структура Матрица с координатами вершин (i x 3), где i - количество вершин у объекта) и значениями каждой вершины */
    char name[SIZE]; /**< Имя объекта */
    double max_value_coordinate; /**< Значение максимальной координаты */
    int count_vertexes; /**< Количество вершин */
    int count_facets; /**< Количество поверхностей */
    int max_vertex; /**< Номер максимальной вершины */
} object_t;

/**
 * @brief Перечисления ошибок
 */
typedef enum {
    CORRECT, /**< Корректно */
    UNCORRECT, /**< Ошибка */
    FILE_NOT_FOUND, /**< Файл не найден */
    EMPTY_FILE, /**< Пустой файл */
    NOT_ENOUGH_MEMORY, /**< Недостаточно памяти в куче*/
} err_t;

/**
 * @brief Функция для обработки данных
 * @param path Путь до файла
 * @return возращает структуру Объекта
 */
int s21_loader(const char* path, object_t* data);

/**
 * @brief Функция для подсчета геометрических параметров
 *
 * Парсит строку и определяет строка является вершиной или поверхностью
 *
 * @param fp Открытый файл
 * @param data Указатель на структуру
 *
 * @return Количество вершин и поверхностей Объекта
 */
void count_geometric_params(FILE *fp, object_t *data);


/**
 * \brief Первый элемент в строке
 *
 * \param str Копия строки
 *
 * \return Возвращает первый буквенный элемент (v / f)
 */
char check_param(char *str);

/**
 * @brief Парсинг строки с данными
 * Заполняет структуру координатами вершин и информацию о поверхностях (v / f)
 * @param fp Открытый файл
 * @param data Указатель на структуру
 *
 * @return Код ошибки
 */
int parse_geometric_params(FILE *fp, object_t *data);

/**
 * @brief Записать значение вершины
 *
 * @param data Объект
 * @param str Копия строки
 * @param ch Передаваемый тип (Вершина/Грань)
 * @param current Номер обрабатываемой вершины (начиная с 0)
 *
 * @return CORRECT / UNCORRECT
 */
int write_value(object_t *data, char *str, int *current);

/**
 * @brief Записать значение вершины
 *
 * @param path Путь до файла
 * @param data Объект
 */
void get_name(const char *path, object_t *data);

/**
 * @brief Геометрические преобразования для корретного отображения объекта 
 *
 * @param data Объект
 */
void s21_geometric_rotations(object_t *data);

/**
 * @brief Центрирование объекта 
 *
 * @param data Объект
 */
void centering_object(object_t *data);

/**
 * @brief Нахождение геометрического центра объекта 
 *
 * @param data Объект
 * @param axis Ось (OX / OY / OZ)
 */
double find_geometric_center(object_t *data, int axis);

/**
 * @brief Перемещение объекта
 *
 * @param data Объект
 * @param axis Ось (OX / OY / OZ)
 * @param axis_coordinate Значение центра (по оси)
 */
void rotate_object(object_t *data, int axis, double axis_coordinate);

/**
 * @brief Возможность отображение объекта
 *
 * Если максимальная величина больше 1, то объект нельзя отобразить 
 * 
 * @param data Объект
 * 
 * @return 0 - нельзя отобразить, 1 - можно отобразить
 */
int is_displayable(object_t *data);

/**
 * @brief Уменьшение объекта
 *
 * @param data Объект
 * @param max_value_coordinate Максимальное значение среди вершин
 */
void reduction_object(object_t *data);

/**
 * @brief Нахождение максимального значения матрицы
 *
 * Функция возвращает максимальное значение матрицы
 * 
 * @param data Объект
 * 
 * @return Максимальное значение матрицы
 */
double find_scale(object_t *data);

/**
 * @brief Удалить структуру объекта
 *
 * @param data Объект
 */
void s21_remove_object(object_t *data);

// Афинные преобразования 

/**
 * @brief Изменить координату X
 *
 * @param data Объект
 * @param move_x Изменяем значение
 */
void s21_move_x(object_t *data, double move_x);

/**
 * @brief Изменить координату Y
 *
 * @param data Объект
 * @param move_y Изменяем значение
 */
void s21_move_y(object_t *data, double move_y);

/**
 * @brief Изменить координату Z
 *
 * @param data Объект
 * @param move_z Изменяем значение
 */
void s21_move_z(object_t *data, double move_z);

/**
 * @brief Перевести угол в радианы
 *
 * @param angle Значение угла
 */
double s21_degres_to_radians(double angle);

/**
 * @brief Поворот объекта по X
 *
 * @param data Объект
 * @param angle Значение угла
 */
void s21_rotate_x(object_t *data, double angle);

/**
 * @brief Поворот объекта по Y
 *
 * @param data Объект
 * @param angle Значение угла
 */
void s21_rotate_y(object_t *data, double angle);

/**
 * @brief Поворот объекта по Z
 *
 * @param data Объект
 * @param angle Значение угла
 */
void s21_rotate_z(object_t *data, double angle);

/**
 * @brief Масштабирование 
 *
 * @param data Объект
 * @param scale Величина масштабирования
 */
void s21_scale(object_t *data, double scale, double prev_scale);

/**
 * @brief Пропустить пробелы в строке 
 *
 * @param str Исходная строка
 */
void skip_spaces(char **str);

/**
 * @brief Проверка на 'v' 
 * 
 * @param str Исходная строка
 */
int is_vertex(const char *str);

#endif // SRC_INCLUDE_S21_3DVIEWER_V1_H_
