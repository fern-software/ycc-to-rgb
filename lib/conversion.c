#include "conversion.h"

#include <stdlib.h>

void single_value_ycc_to_rgb(struct ycc_pixel *pixel, struct rgb_pixel *rgb_pixel) {
    double Y = (double) pixel->y;
    double Cb = (double) pixel->cb;
    double Cr = (double) pixel->cr;

    int r = (int) (Y + 1.40200 * (Cr - 128));
    int g = (int) (Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128));
    int b = (int) (Y + 1.77200 * (Cb - 128));

    // Clip values to [0, 255]
    rgb_pixel->r = Max(0, Min(255, r));
    rgb_pixel->g = Max(0, Min(255, g));
    rgb_pixel->b = Max(0, Min(255, b));
}

void ycc_to_rgb(struct ycc_img* src_img, struct rgb_img* dst_img){
    dst_img->width = src_img->width;
    dst_img->height = src_img->height;
    dst_img->data = malloc(dst_img->width * dst_img->height * sizeof(struct rgb_pixel));
    if(!dst_img->data){
        return;
    }
    
    for(int i = 0; i < dst_img->width * dst_img->height; ++i){
        struct ycc_pixel* src_pixel = &src_img->data[i];
        struct rgb_pixel* dst_pixel = &dst_img->data[i];
        single_value_ycc_to_rgb(src_pixel, dst_pixel);
    }
}