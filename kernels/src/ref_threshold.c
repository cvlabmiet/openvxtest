/*! @file
 *  @brief Содержит эталонную реализацию пороговой обработки.
 *  @author Панфилова Кристина
 *  @date: 19 Августа 2015
 */

#include "detail/types.h"

vx_status ref_threshold(const vx_image src_image, vx_image dst_image, const vx_threshold thresh)
{
    if (thresh->threshold_type != VX_THRESHOLD_TYPE_BINARY && thresh->threshold_type != VX_THRESHOLD_TYPE_RANGE)
        return VX_ERROR_INVALID_PARAMETERS;

    const uint32_t src_width = src_image->width;
    const uint32_t src_height = src_image->height;
    const uint32_t dst_width = dst_image->width;
    const uint32_t dst_height = dst_image->height;

    if (src_width != dst_width || src_height != dst_height)
        return VX_ERROR_INVALID_PARAMETERS;

    const uint8_t* src_data = src_image->data;
    uint8_t* dst_data = dst_image->data;

    if (thresh->threshold_type == VX_THRESHOLD_TYPE_BINARY)
    {
        for (uint32_t ind = 0; ind < src_width * src_height; ++ind)
            dst_data[ind] = -1*(src_data[ind] > thresh->value);
    }
    else
    {
        for (uint32_t ind = 0; ind < src_width * src_height; ++ind)
            dst_data[ind] = -1*(src_data[ind] >= thresh->lower_threshold && src_data[ind] <= thresh->upper_threshold);
    }

    return VX_SUCCESS;
}
