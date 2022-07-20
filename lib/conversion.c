#include <stdlib.h>

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

// TODO: pass by value might be able to be optimized away
void single_value_ycc_to_rgb(uint8_t y, uint8_t cb, uint8_t cr, struct rgb_pixel *rgb_pixel) {
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

void ycc_to_rgb(struct ycc_img* src_img, struct rgb_img* dst_img){
    dst_img->width = src_img->width * 2;
    dst_img->height = src_img->height * 2;
    dst_img->data = malloc(dst_img->width * dst_img->height * sizeof(struct rgb_pixel));
    if(!dst_img->data){
        return;
    }
    
    // TODO: loop could be optimized by changing the i * 4 to a bitshift
    for(int i = 0; i < src_img->width * src_img->height; ++i){
        struct ycc_pixel pix = src_img->data[i];
        single_value_ycc_to_rgb(pix.y_tl, pix.cb, pix.cr, &dst_img->data[i * 4]);
        single_value_ycc_to_rgb(pix.y_tr, pix.cb, pix.cr, &dst_img->data[(i * 4) + 1]);
        single_value_ycc_to_rgb(pix.y_bl, pix.cb, pix.cr, &dst_img->data[(i * 4) + 2]);
        single_value_ycc_to_rgb(pix.y_br, pix.cb, pix.cr, &dst_img->data[(i * 4) + 3]);
    }
}

void rgb_to_ycc(struct rgb_img *src_img, struct ycc_img *dst_img){
    dst_img->width = src_img->width / 2;
    dst_img->height = src_img->height / 2;
    dst_img->data = malloc(dst_img->width * dst_img->height * sizeof(struct ycc_pixel));
    
    uint8_t* fullres_cb = malloc(src_img->width * src_img->height);
    uint8_t* fullres_cr = malloc(src_img->width * src_img->height);

    if(!dst_img->data || !fullres_cb || !fullres_cr){
        return;
    }
    
    for(int i = 0; i < src_img->width * src_img->height; ++i){
        uint8_t y = rgb_to_y(&(src_img->data[i]));
        switch(i % 4){
            case 0:
                (dst_img->data[i / 4]).y_tl = y;
                break;
            case 1:
                (dst_img->data[i / 4]).y_tr = y;
                break;
            case 2:
                (dst_img->data[i / 4]).y_bl = y;
                break;
            case 3:
                (dst_img->data[i / 4]).y_br = y;
                break;
        }
        
        fullres_cb[i] = rgb_to_cb(&(src_img->data[i]));
        fullres_cr[i] = rgb_to_cr(&(src_img->data[i]));
    }

    // Downsample Cb and Cr by averaging the values of neighboring pixels.
    for(int i = 0; i < dst_img->width * dst_img->height; ++i){
        (dst_img->data[i]).cb = (uint8_t)((fullres_cb[i * 4] + fullres_cb[(i * 4) + 1] + fullres_cb[(i * 4) + dst_img->width] + fullres_cb[(i * 4) + dst_img->width + 1]) / 4);
        (dst_img->data[i]).cr = (uint8_t)((fullres_cr[i * 4] + fullres_cr[(i * 4) + 1] + fullres_cr[(i * 4) + dst_img->width] + fullres_cr[(i * 4) + dst_img->width + 1]) / 4);
    }

    free(fullres_cb);
    free(fullres_cr);
}