/*
File: ref_FindAllContours.c
*/

#include "../ref.h"

vx_status ref_FindAllContours(const vx_image src_image,
	vx_image dst_image)
{

	const uint32_t src_width = src_image->width;
	const uint32_t src_height = src_image->height;
	const uint32_t dst_width = dst_image->width;
	const uint32_t dst_height = dst_image->height;

	if (src_image->image_type != dst_image->image_type || src_image->color_space != dst_image->color_space)
	{
		return VX_ERROR_INVALID_PARAMETERS;
	}

	if (src_width != dst_width || src_height != dst_height)
	{
		return VX_ERROR_INVALID_PARAMETERS;
	}

	const uint8_t* src_data = src_image->data;
	uint8_t* dst_data = dst_image->data;

	const uint32_t width2 = src_width + 2;
	uint8_t* r_src;
	uint8_t* r_dst;
	r_src = (uint8_t*)calloc((src_width + 2)*(src_height + 2), sizeof(uint8_t));
	r_dst = (uint8_t*)calloc((src_width + 2)*(src_height + 2), sizeof(uint8_t));
	for (uint32_t ind = 0; ind < (src_width + 2); ind++)
	{
		r_src[ind] = 0;
		r_src[(src_width + 2)*(src_height + 1) + ind] = 0;
	}
	for (uint32_t ind = (src_width + 2); ind < (src_width + 2)*(src_height + 1); ind++)
	{
		r_dst[ind] = 0;
		if ((ind % width2 == 0) || ((ind + 1) % width2 == 0))
			r_src[ind] = 0;
		else
		{
			r_src[ind] = src_data[(ind / width2 - 1) * src_width + ((ind % width2) - 1)];
		}
	}
	for (uint32_t ind = (width2 + 1); ind < width2 * (src_height + 1); ind++)
	{
		if ((r_src[ind] == 255) && (r_dst[ind] == 0) && ((r_src[ind - 1] == 0) || (r_src[ind + 1] == 0) || (r_src[ind - width2] == 0) || (r_src[ind + width2] == 0)))
		{
			uint32_t b0 = ind, b = ind, b1, c0;
			if (r_src[ind - 1] == 0) c0 = ind - 1;
			else if (r_src[ind + 1] == 0) c0 = ind + 1;
			else if (r_src[ind - width2] == 0) c0 = ind - width2;
			else if (r_src[ind + width2] == 0) c0 = ind + width2;
			uint32_t c = c0;
			r_dst[ind] = 255;
			moor(r_src, r_dst, &b, &c, width2);
			b1 = b;
			vx_bool bl = vx_true_e; 
			while (bl)
			{
				moor(r_src, r_dst, &b, &c, width2);
				if (b == b0)
				{
					moor(r_src, r_dst, &b, &c, width2);
					if (b == b1)
						bl = vx_false_e;
				}
			}
		}
	}
	for (uint32_t ind = (src_width + 2); ind < (src_width + 2)*(src_height + 1); ind++)
	{
		if ((ind % width2 != 0) && ((ind + 1) % width2 != 0))
		{
			dst_data[(ind / width2 - 1) * src_width + ((ind % width2) - 1)] = r_dst[ind];
		}
	}
	return VX_SUCCESS;
}
