#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "conversion.h"

void ycc_to_rgb(struct ycc_img* src_img, struct rgb_img* dst_img){
    dst_img->width = src_img->width * 2;
    dst_img->height = src_img->height * 2;
    dst_img->data = malloc(dst_img->width * dst_img->height * sizeof(struct rgb_pixel));
    if(!dst_img->data){
        return;
    }
    
    // TODO: loop could be optimized
    for(int i = 0; i < src_img->height; ++i){
        for(int j = 0; j < src_img->width; ++j){
            struct ycc_pixel pix = src_img->data[i * src_img->width + j];
            single_value_ycc_to_rgb(pix.y_tl, pix.cb, pix.cr, &(dst_img->data[i * 2 * dst_img->width + j * 2]));
            single_value_ycc_to_rgb(pix.y_tr, pix.cb, pix.cr, &(dst_img->data[i * 2 * dst_img->width + j * 2 + 1]));
            single_value_ycc_to_rgb(pix.y_bl, pix.cb, pix.cr, &(dst_img->data[i * 2 * dst_img->width + j * 2 + dst_img->width]));
            single_value_ycc_to_rgb(pix.y_br, pix.cb, pix.cr, &(dst_img->data[i * 2 * dst_img->width + j * 2 + dst_img->width + 1]));
        }
    }
}

// NOTE:
// everything underneath this comment was created for generating test data solely
// it is un-optimized as optimizing it is out of the scope of this project

uint8_t rgb_to_y(struct rgb_pixel *rgb_pixel) {
    return (uint8_t)(0.299 * rgb_pixel->r + 0.587 * rgb_pixel->g + 0.114 * rgb_pixel->b);
}

uint8_t rgb_to_cb(struct rgb_pixel *rgb_pixel) {
    return (uint8_t)(-0.1687 * rgb_pixel->r - 0.3313 * rgb_pixel->g + 0.5 * rgb_pixel->b + 128);
}

uint8_t rgb_to_cr(struct rgb_pixel *rgb_pixel) {
    return (uint8_t)(0.5 * rgb_pixel->r - 0.4187 * rgb_pixel->g - 0.0813 * rgb_pixel->b + 128);
}

void rgb_to_ycc(struct rgb_img *src_img, struct ycc_img *dst_img){
    dst_img->width = src_img->width / 2;
    dst_img->height = src_img->height / 2;
    dst_img->data = malloc(dst_img->width * dst_img->height * sizeof(struct ycc_pixel));
    
    uint16_t* cb_accumulator = malloc(src_img->width * src_img->height * sizeof(uint16_t));
    uint16_t* cr_accumulator = malloc(src_img->width * src_img->height * sizeof(uint16_t));

    if(!dst_img->data || !cb_accumulator || !cr_accumulator){
        return;
    }

    memset(cb_accumulator, 0, src_img->width * src_img->height * sizeof(uint16_t));
    memset(cr_accumulator, 0, src_img->width * src_img->height * sizeof(uint16_t));
    
    for(int i = 0; i < src_img->height; ++i){
        for(int j = 0; j < src_img->width; ++j){
            uint8_t y = rgb_to_y(&(src_img->data[i * src_img->width + j]));
            
            if(i % 2 == 0){
                if(j % 2 == 0){
                    (dst_img->data[(i / 2) * dst_img->width + (j / 2)]).y_tl = y;
                }
                else{
                    (dst_img->data[(i / 2) * dst_img->width + (j / 2)]).y_tr = y;
                }
            }
            else {
                if(j % 2 == 0){
                    (dst_img->data[(i / 2) * dst_img->width + (j / 2)]).y_bl = y;
                }
                else{
                    (dst_img->data[(i / 2) * dst_img->width + (j / 2)]).y_br = y;
                }
            }

            cb_accumulator[(i / 2) * dst_img->width + (j / 2)] += rgb_to_cb(&(src_img->data[i * src_img->width + j]));
            cr_accumulator[(i / 2) * dst_img->width + (j / 2)] += rgb_to_cr(&(src_img->data[i * src_img->width + j]));
        }
    }

    // Downsample Cb and Cr by averaging the values of neighboring pixels.
    for(int i = 0; i < dst_img->height * dst_img->width; ++i){
        (dst_img->data[i]).cb = (uint8_t) (cb_accumulator[i] / 4);
        (dst_img->data[i]).cr = (uint8_t) (cr_accumulator[i] / 4);
    }

    free(cb_accumulator);
    free(cr_accumulator);
}
