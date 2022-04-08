/*! @file
 *  @brief Содержит структуры данных, используемые в функциях openvx
 *  @author Роман Голованов
 *  @date: 21 Августа 2015
 */

#ifndef __TYPES_H0__
#define __TYPES_H0__

#include <stdint.h>
#include <stdbool.h>

#include "../openvx/vx.h"

//! Cтруктура для хранения значения порога.
struct _vx_threshold
{
    enum vx_threshold_type_e threshold_type; //!< Тип порога.
    uint8_t value; //!< Значение порога (для Binary).
    uint8_t upper_threshold; //!< Значение верхнего порога.
    uint8_t lower_threshold; //!< Значение нижнего порога.
};

//! Cтруктура для хранения изображения.
struct _vx_image
{
    void* data; //!< Указатель на область памяти с изображением.
    uint32_t width; //!< Ширина изображения.
    uint32_t height; //!< Высота изображения.
    enum vx_df_image_e image_type; //!< Тип изображения.
    enum vx_color_space_e color_space; //!< Цветовое пространство.
};

//! Cтруктура для хранения матрицы преобразования.
struct _vx_remap
{
    float* x; //!< Указатель на массив с координатами по оси x.
    float* y; //!< Указатель на массив с координатами по оси y.
    uint32_t height; //!< Высота матрицы.
    uint32_t width; //!< Ширина матрицы.
};

//! Cтруктура для хранения скаляра.
struct _vx_scalar
{
    void* value; //!< Указатель на значение скаляра.
    enum vx_type_e scalar_type; //!< Тип скаляра.
};

//! Cтруктура для хранения массива.
struct _vx_array
{
    void* data; //!< Указатель на содержимое массива.
    uint32_t size; //!< Размер массива.
    enum vx_type_e array_type; //!< Тип элементов массива.
};

//! Cтруктура для хранения распределения.
struct _vx_distribution
{
    uint32_t* distribution; //!< Указатель на значения распределения.
    uint32_t size; //!< Размер распределения.
};

//! Cтруктура для хранения таблиц переходов.
struct _vx_lut
{
    uint8_t* data; //!< Указатель на содержимое таблицы.
    uint32_t size; //!< Размер таблицы.
};

//! Cтруктура для хранения матрицы.
struct _vx_matrix
{
    void* data; //!< Указатель на содержимое матрицы.
    uint32_t height; //!< Высота матрицы.
    uint32_t width; //!< Ширина матрицы.
    enum vx_type_e array_type; //!< Тип элементов массива.
};

//! Cтруктура для хранения ядра свертки.
struct _vx_convolution
{
    int16_t* coefficients; //!< Указатель на коэффициенты.
    uint32_t width; //!< Ширина.
    uint32_t height; //!< Высота.
    uint32_t scale; //!< Масштаб.
};

//! Cтруктура для хранения координат углов на изображении.
struct _vx_keypoint
{
    int32_t x; //!< Координата x.
    int32_t y; //!< Координата y.
    float strength; //!< Сила характерной точки.
};

//! Cтруктура для хранения пирамиды изображений.
struct _vx_pyramid {
    size_t numLevels; //!< Количество уровней в пирамиде.
    vx_image *levels; //!< Указатель на изображения пирамиды.
    float scale; //!< Масштабный коэффициент.
    uint32_t width; //!< Ширина.
    uint32_t height; //!< Высота.
    enum vx_df_image_e image_type; //!< Тип изображений для всех уровней.
};

#endif //__TYPES_H0__
