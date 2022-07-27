#pragma once

#include "util.h"

// Converts a single YCC pixel to an RGB pixel.
// TODO: pass by value might be able to be optimized away
static inline void single_value_ycc_to_rgb(uint8_t y, uint8_t cb, uint8_t cr, struct rgb_pixel *rgb_pixel) {
    double Y = (double) y;
    double Cb = (double) cb;
    double Cr = (double) cr;

    int r = (int) (Y + 1.40200 * (Cr - 128));
    int g = (int) (Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128));
    int b = (int) (Y + 1.77200 * (Cb - 128));

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
