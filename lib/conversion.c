#include "util.h"
#include "conversion.h"


uint8_t rgb_to_y(struct rgb_pixel *rgb_pixel) {
    return (uint8_t)(0.299 * rgb_pixel->r + 0.587 * rgb_pixel->g + 0.114 * rgb_pixel->b);
}

uint8_t rgb_to_cb(struct rgb_pixel *rgb_pixel) {
    return (uint8_t)(-0.1687 * rgb_pixel->r - 0.3313 * rgb_pixel->g + 0.5 * rgb_pixel->b + 128);
}

uint8_t rgb_to_cr(struct rgb_pixel *rgb_pixel) {
    return (uint8_t)(0.5 * rgb_pixel->r - 0.4187 * rgb_pixel->g - 0.0813 * rgb_pixel->b + 128);
}

void single_value_ycc_to_rgb(uint8_t *y, uint8_t *cb, uint8_t *cr, struct rgb_pixel *rgb_pixel) {
    double Y = (double) *y;
    double Cb = (double) *cb;
    double Cr = (double) *cr;

    int r = (int) (Y + 1.40200 * (Cr - 128));
    int g = (int) (Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128));
    int b = (int) (Y + 1.77200 * (Cb - 128));

    // Clip values to [0, 255]
    rgb_pixel->r = max(0, min(255, r));
    rgb_pixel->g = max(0, min(255, g));
    rgb_pixel->b = max(0, min(255, b));
}

void ycc_to_rgb(struct ycc_img* src_img, struct rgb_img* dst_img){
    dst_img->width = src_img->width;
    dst_img->height = src_img->height;
    dst_img->data = malloc(dst_img->width * dst_img->height * sizeof(struct rgb_pixel));
    if(!dst_img->data){
        return;
    }
    
    for(int i = 0; i < dst_img->width * dst_img->height; ++i){
        single_value_ycc_to_rgb(&src_img->y[i], &src_img->cb[i], &src_img->cr[i], &dst_img->data[i]);
    }
}

void rgb_to_ycc(struct rgb_img *src_img, struct ycc_img *dst_img) {
    dst_img->width = src_img->width;
    dst_img->height = src_img->height;
    dst_img->y = malloc(dst_img->width * dst_img->height * sizeof(uint8_t));
    dst_img->cb = malloc((dst_img->width * dst_img->height * sizeof(uint8_t)) / 4);
    dst_img->cr = malloc((dst_img->width * dst_img->height * sizeof(uint8_t)) / 4);
    uint8_t fullres_cb[dst_img->width * dst_img->height];
    uint8_t fullres_cr[dst_img->width * dst_img->height];

    if(!dst_img->y || !dst_img->cb || !dst_img->cr){
        return;
    }
    
    for(int i = 0; i < dst_img->width * dst_img->height; ++i){
        dst_img->y[i] = rgb_to_y(&src_img->data[i]);
        fullres_cb[i] = rgb_to_cb(&src_img->data[i]);
        fullres_cr[i] = rgb_to_cr(&src_img->data[i]);
    }

    // Downsample Cb and Cr by averaging the values of neighboring pixels.
    for(int i = 0; i < dst_img->width * dst_img->height; i+=4){
        dst_img->cb[i] = (uint8_t)((fullres_cb[i] + fullres_cb[i + 1] + fullres_cb[i + dst_img->width] + fullres_cb[i + dst_img->width + 1]) / 4);
        dst_img->cr[i] = (uint8_t)((fullres_cr[i] + fullres_cr[i + 1] + fullres_cr[i + dst_img->width] + fullres_cr[i + dst_img->width + 1]) / 4);
    }

}