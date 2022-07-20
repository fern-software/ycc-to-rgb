#pragma once

#include "util.h"

// Converts a single YCC pixel to an RGB pixel.
void single_value_ycc_to_rgb(uint8_t y, uint8_t cb, uint8_t cr, struct rgb_pixel *rgb_pixel);

// Converts a YCC image to an RGB image.
// Note: allocates (width*height*sizeof(rgb_pixel)) memory for dst_img. This can most likely be optimized.
void ycc_to_rgb(struct ycc_img *src_img, struct rgb_img *dst_img);

// Converts an RGB image to YCC
// Downsamples Cb and Cr by averaging the values of neighboring pixels.
// Unoptimized, used for generating test data
void rgb_to_ycc(struct rgb_img *src_img, struct ycc_img *dst_img);

// Generates a Y value from an RGB pixel
uint8_t rgb_to_y(struct rgb_pixel *rgb_pixel);

// Generates a Cb value from an RGB pixel
uint8_t rgb_to_cb(struct rgb_pixel *rgb_pixel);

// Generates a Cr value from an RGB pixel
uint8_t rgb_to_cr(struct rgb_pixel *rgb_pixel);
