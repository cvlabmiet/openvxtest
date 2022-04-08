/*! @file
 *  @brief Содержит объявления эталонных реализаций функций OpenVX. Функции выполняются только на RISC.
 *  @author Роман Голованов
 *  @date: 19 Августа 2015
 */

#ifndef __KERNELS_H__
#define __KERNELS_H__

#include "openvx/vx.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @brief ПРИМЕР РЕАЛИЗОВАННОЙ ФУНКЦИИ пороговой обработки
 *  Binary:
 *      Если яркость пикселя больше порога, то значение соответствующего пикселя выходного изображения
 *      устанавливается в 255, иначе в 0.
 *  Range:
 *      Если яркость пикселя больше верхнего порога и меньше нижнего, то значение соответствующего пикселя
 *      выходного изображения устанавливается в 0, иначе в 255.
 *  @param[in] src_image входное изображение
 *  @param[out] dst_image выходное изображение
 *  @param[in] thresh структура, состоящая из трёх полей:
 *      - значение порога для binary (value);
 *      - значение верхнего порога для range (upper_thresholding);
 *      - значение нижнего порога для range (lower_thresholding)
 *  @reval VX_SUCCESS в случае успешного завершения
 *  @retval VX_ERROR_INVALID_PARAMETERS в случае некорректных данных
 */
vx_status ref_threshold(const vx_image src_image, vx_image dst_image, const vx_threshold thresh);

#ifdef __cplusplus
}
#endif

#endif // __KERNELS_H__
