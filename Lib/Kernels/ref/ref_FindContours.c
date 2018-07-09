/*
File: ref_FindContours.c.
*/

//#include "../../../Demo/stdafx.h"
#include "../ref.h"


inline uint8_t func(uint32_t b, uint32_t c, uint32_t width)
{
	if (b > c)
	{
		if ((b - c) == 1)
			return 0;
		else if ((b - c) == (width + 1))
			return 1;
		else if ((b - c) == width)
			return 2;
		else if ((b - c) == (width - 1))
			return 3;
	}
	else
	{
		if ((c - b) == 1)
			return 4;
		else if ((c - b) == (width + 1))
			return 5;
		else if ((c - b) == width)
			return 6;
		else if ((c - b) == (width - 1))
			return 7;
	}
}

inline uint32_t func2(uint32_t b, uint32_t width, uint8_t pos)
{
	pos = pos % 8;
	if (pos == 0)
		return (b - 1);
	else if (pos == 1)
		return (b - width - 1);
	else if (pos == 2)
		return (b - width);
	else if (pos == 3)
		return (b - width + 1);
	else if (pos == 4)
		return (b + 1);
	else if (pos == 5)
		return (b + width + 1);
	else if (pos == 6)
		return (b + width);
	else if (pos == 7)
		return (b + width - 1);
}

void moor(uint8_t* src_d,
	uint8_t* dst_d,
	uint32_t* b,
	uint32_t* c,
	uint32_t width)
{
	vx_bool end = vx_true_e;
	uint8_t pos = func(*b, *c, width);
	uint8_t count = 0;
	while (end)
	{
		if (src_d[func2(*b, width, ((pos + 1) % 8))] == 255)
		{
			dst_d[func2(*b, width, ((pos + 1) % 8))] = 255;
			*c = func2(*b, width, pos);
			*b = func2(*b, width, ((pos + 1) % 8));
			end = vx_false_e;
		}
		else
		{
			count++;
			if (count == 7) end = vx_false_e;
			pos = (pos + 1) % 8;
		}
	}
}

void grow(uint8_t* src, uint32_t* dst, uint32_t ind, uint32_t number, uint32_t width, uint32_t* vect, uint32_t* vect2, uint32_t maxsize)
{
	vect[0] = ind;
	uint32_t count_prev = 1;
	uint32_t count = 1;
	uint8_t pos = 1;
	while (count > 0)
	{
		count = 0;
		pos = 0;
		for (uint32_t i = 0; i < count_prev; i++)
		{
			pos = 0;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			pos++;
			if ((src[func2(vect[i], width, pos)] == 255) && (dst[func2(vect[i], width, pos)] == 0)) {
				dst[func2(vect[i], width, pos)] = number;
				vect2[count] = func2(vect[i], width, pos);
				count++;
			}
			if (count>=(maxsize - 8))
			{
				count = count % maxsize;
			}
		}
		count_prev = count;
		uint32_t* ptr;
		ptr = vect;
		vect = vect2;
		vect2 = ptr;
	}
}
vx_status ref_FindContours(const vx_image src_image,
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

	// extended matrices
	const uint32_t width2 = src_width + 2;
	uint8_t* r_src;
	uint32_t* r_src2;
	uint8_t* r_dst;
	uint32_t* vect;
	uint32_t* vect2;
	uint32_t sizeofVect = (src_height+src_width);
	r_src = (uint8_t*)calloc((src_width + 2)*(src_height + 2), sizeof(uint8_t));
	r_src2 = (uint32_t*)calloc((src_width + 2)*(src_height + 2), sizeof(uint32_t));
	r_dst = (uint8_t*)calloc((src_width + 2)*(src_height + 2), sizeof(uint8_t));
	vect = (uint32_t*)calloc(sizeofVect, sizeof(uint32_t));
	vect2 = (uint32_t*)calloc(sizeofVect, sizeof(uint32_t));

	for (uint32_t ind = 0; ind < (src_width + 2); ind++)
	{
		r_src[ind] = 0;
		r_src[(src_width + 2)*(src_height + 1) + ind] = 0;
		r_src2[ind] = 0;
		r_src2[(src_width + 2)*(src_height + 1) + ind] = 0;
	}
	for (uint32_t ind = (src_width + 2); ind < (src_width + 2)*(src_height + 1); ind++)
	{
		r_dst[ind] = 0;
		r_src2[ind] = 0;
		if ((ind % width2 == 0) || ((ind + 1) % width2 == 0))
			r_src[ind] = 0;
		else
		{
			r_src[ind] = src_data[(ind / width2 - 1) * src_width + ((ind % width2) - 1)];
		}
	}
	uint32_t number = 0;
	for (uint32_t ind = (width2 + 1); ind < width2 * (src_height + 1); ind++)
	{
		if ((r_src[ind] == 255) && (r_src2[ind] == 0))
		{
			number++;
			r_src2[ind] = number;
			grow(r_src, r_src2, ind, number, width2, vect, vect2, sizeofVect);
		}
	}

	uint32_t counter_number = 1;
	uint32_t index = (width2 + 1);
	uint8_t scaleOfNumber = 255 / number;
	while ((counter_number <= number) && (index < (src_width + 2)*(src_height + 1)))
	{
		if ((r_src2[index] == counter_number) && (r_dst[index] == 0))
		{
			uint32_t b0 = index, b = index, b1;
			uint32_t c = index - 1;
			r_dst[index] = 255;
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
					{
						counter_number++;
						bl = vx_false_e;
					}
				}
			}
		}
		index++;
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
