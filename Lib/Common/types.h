/*
    File: types.h
    Содержит структуры данных, используемые в функциях openvx

    Author: Роман Голованов

    Date: 21 Августа 2015
*/
#ifndef __TYPES_H0__
#define __TYPES_H0__

#include <stdint.h>
#include <stdbool.h>

#include "openvx/vx.h"

#pragma warning(disable: 4820) // suppress 1 byte padding for vx_threshold

/*
    Structure: _vx_threshold
    Cтруктура для хранения значения порога.
*/

struct _vx_threshold
{
    //Variable: threshold_type
    //тип порога;
    enum vx_threshold_type_e threshold_type;
    //Variable: value
    //значение порога (для Binary);
    uint8_t value;
    //Variable: address
    //значение верхнего порога;
    uint8_t upper_threshold;
    //Variable: lower_threshold
    //значение нижнего порога.
    uint8_t lower_threshold;
};

#pragma warning(default: 4820)

/*
    Structure: _vx_image
    Cтруктура для хранения изображения.
*/
struct _vx_image
{
    //Variable: data
    //указатель на область памяти с изображением;
    void* data;
    //Variable: width
    //ширина изображения;
    uint32_t width;
    //Variable: height
    //высота изображения;
    uint32_t height;
    //Variable: image_type
    //тип изображения;
    enum vx_df_image_e image_type;
    //Variable: color_space
    //цветовое пространство.
    enum vx_color_space_e color_space;
};

/*
    Structure: _vx_remap
    Cтруктура для хранения матрицы преобразования.
*/
struct _vx_remap
{
    //Variable: x
    //указатель на массив с координатами по оси x;
    float* x;
    //Variable: y
    //указатель на массив с координатами по оси y;
    float* y;
    //Variable: height
    //высота матрицы;
    uint32_t height;
    //Variable: width
    //ширина матрицы.
    uint32_t width;
};

/*
    Structure: _vx_scalar
    Cтруктура для хранения скаляра.
*/
struct _vx_scalar
{
    //Variable: value
    //указатель на значение скаляра;
    void* value;
    //Variable: scalar_type
    //тип скаляра.
    enum vx_type_e scalar_type;
};

/*
    Structure: _vx_array
    Cтруктура для хранения массива.
*/
struct _vx_array
{
    //Variable: data
    //указатель на содержимое массива;
    void* data;
    //Variable: size
    //размер массива;
    uint32_t size;
    //Variable: array_type
    //тип элементов массива.
    enum vx_type_e array_type;
};

/*
    Structure: _vx_distribution
    Cтруктура для хранения распределения.
*/
struct _vx_distribution
{
    //Variable: distribution
    //указатель на значения распределения;
    uint32_t* distribution;
    //Variable: size
    //размер распределения.
    uint32_t size;
};

/*
    Structure: _vx_distribution
    Cтруктура для хранения таблиц переходов.
*/
struct _vx_lut
{
    //Variable: data
    //указатель на содержимое таблицы;
    uint8_t* data;
    //Variable: size
    //размер таблицы.
    uint32_t size;
};

/*
    Structure: _vx_matrix
    Cтруктура для хранения матрицы.
*/
struct _vx_matrix
{
    //Variable: data
    //указатель на содержимое матрицы;
    void* data;
    //Variable: height
    //высота матрицы;
    uint32_t height;
    //Variable: width
    //ширина матрицы.
    uint32_t width;
    //Variable: array_type
    //тип элементов массива.
    enum vx_type_e array_type;
};
/*
    Structure: _vx_convolution
    Cтруктура для хранения ядра свертки.
*/
typedef struct _vx_convolution
{
    //Variable: coefficients
    //указатель на коэффициенты;
    int16_t* coefficients;
    //Variable: width
    //ширина;
    uint32_t width;
    //Variable: height
    //высота;
    uint32_t height;
    //Variable: scale
    //масштаб.
    uint32_t scale;
} vx_convolution_t;

/*
    Structure: _vx_keypoint
    Cтруктура для хранения координат углов на изображении.
*/
typedef struct _vx_keypoint
{
    //Variable: x
    //координата x;
    int32_t x;
    //Variable: y
    //координата y;
    int32_t y;
    //Variable: strength
    //сила характерной точки;
    float strength;
} vx_keypoint;

struct _vx_pyramid {
    //Variable: numLevels
    //Количество уровней в пирамиде;
    size_t numLevels;
    //Variable: levels
    //указатель на изображения пирамиды;
    vx_image *levels;
    //Variable: scale
    //масштабный коэффициент;
    float scale;
    //Variable: width
    //ширина;   
    uint32_t width;
    //Variable: height
    //высота;
    uint32_t height;
    //Variable: image_type
    //тип изображений для всех уровней;   
    enum vx_df_image_e image_type;
};

#endif //__TYPES_H0__
