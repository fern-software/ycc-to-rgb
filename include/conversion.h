#pragma once

#include "util.h"


void single_value_ycc_to_rgb(struct ycc_pixel *pixel, struct rgb_pixel *rgb_pixel);

void ycc_to_rgb(struct ycc_img *src_img, struct rgb_img *dst_img);