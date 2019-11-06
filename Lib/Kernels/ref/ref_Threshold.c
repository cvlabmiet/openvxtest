/*
    File: ref_Threshold.c
    Содержит эталонную реализацию пороговой обработки.

    Author: Панфилова Кристина

    Date: 19 Августа 2015
*/

#include "../ref.h"

vx_status ref_Threshold(const vx_image src_image,
                        vx_image dst_image,
                        const vx_threshold thresh)
{
    if (thresh->threshold_type != VX_THRESHOLD_TYPE_BINARY && thresh->threshold_type != VX_THRESHOLD_TYPE_RANGE)
    {
        return VX_ERROR_INVALID_PARAMETERS;
    }

    const uint32_t src_width = src_image->width;
    const uint32_t src_height = src_image->height;
    const uint32_t dst_width = dst_image->width;
    const uint32_t dst_height = dst_image->height;

    if (src_width != dst_width || src_height != dst_height)
    {
        return VX_ERROR_INVALID_PARAMETERS;
    }

    const uint8_t* src_data = src_image->data;
    uint8_t* dst_data = dst_image->data;

    for (uint32_t ind = 0; ind < src_width * src_height; ++ind)
    {
        if (thresh->threshold_type == VX_THRESHOLD_TYPE_BINARY)
        {
            if (src_data[ind] > thresh->value)
            {
                dst_data[ind] = 255;
            }
            else
            {
                dst_data[ind] = 0;
            }
        }
        else
        {
            if (src_data[ind] > thresh->upper_threshold)
            {
                dst_data[ind] = 0;
            }
            else
            {
                if (src_data[ind] < thresh->lower_threshold)
                {
                    dst_data[ind] = 0;
                }
                else
                {
                    dst_data[ind] = 255;
                }
            }
        }
    }

    return VX_SUCCESS;
}
