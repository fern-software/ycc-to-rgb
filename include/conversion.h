#pragma once

#include "util.h"

// Converts a single YCC pixel to an RGB pixel.
void single_value_ycc_to_rgb(struct ycc_pixel *pixel, struct rgb_pixel *rgb_pixel);

// Converts a YCC image to an RGB image.
// Note: allocates (width*height*sizeof(rgb_pixel)) memory for dst_img. This can most likely be optimized.
void ycc_to_rgb(struct ycc_img *src_img, struct rgb_img *dst_img);