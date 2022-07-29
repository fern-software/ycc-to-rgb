#pragma once

#include "util.h"

// Converts a single YCC pixel to an RGB pixel using fixed point arithmetic.
//
// we will use integer multiplication instead of fractional multiplication
// this will give us results that are 32 bits
//
// since the multiplier constants will not change we will use
// and are all smaller than 2 we will use 2^15 / 2^1 = 2^14
// as our scale factors for the constants
//
// ycc values are in the range [-128, 127]
// this gives a scale factor of 2^15 / 2^7 = 2^8 for cb, and cr
//
// y is a little different however since we only add and substract it
// it must have the same factor as a constant multiplied by cb or cr
// this would be 2^8 * 2^14 = 2^22
static inline void single_value_ycc_to_rgb(uint8_t y, uint8_t cb, uint8_t cr, struct rgb_pixel *rgb_pixel) {
    // scale up
    int32_t Y = ((int32_t) y) << 22;
    int32_t Cb = (((int32_t) cb) - 128) << 8;
    int32_t Cr = (((int32_t) cr) - 128) << 8;

    // 1.40200 << 14
    register int32_t r_mul = 22970;

    // 0.34414 << 14
    register int32_t g_cb_mul = 5638;

    // 0.71414 << 14
    register int32_t g_cr_mul = 11700; 

    // 1.77200 << 14
    register int32_t b_mul = 29032;

    // multiply and scale down
    int32_t r = ((Y + r_mul * Cr)) >> 22;
    int32_t g = ((Y - g_cb_mul * Cb) - (g_cr_mul * Cr)) >> 22;
    int32_t b = ((Y + b_mul * Cb)) >> 22;

    // Clip values to [0, 255]
    rgb_pixel->r = max(0, min(255, r));
    rgb_pixel->g = max(0, min(255, g));
    rgb_pixel->b = max(0, min(255, b));
}

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
