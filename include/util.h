#pragma once

#include <stdint.h>

// struct to hold a ycc pixel in 4:2:0 format where there are 4 ys for every cb and cr
struct ycc_pixel {
	uint8_t y_tl;
	uint8_t y_tr;
	uint8_t y_bl;
	uint8_t y_br;
	uint8_t cb;
	uint8_t cr;
};

struct ycc_img {
	struct ycc_pixel* data;
	unsigned int width;
	unsigned int height;
};

struct rgb_pixel {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct rgb_img {
	struct rgb_pixel* data;
	unsigned int width;
	unsigned int height;
};

// // Returns the smaller of a,b. If a==b, returns a.
// int min(int a, int b);

// // Returns the larger of a,b. If a==b, returns a.
// int max(int a, int b);

static inline int min(int a, int b){
	if(a <= b){
		return a;
	}
	return b;
}

static inline int max(int a, int b){
	if(a >= b){
		return a;
	}
	return b;
}

// reads a YCC image stored at filename and populates image with its data
// returns a non-zero value on success, 0 on failure
int read_ycc_img(char* filename, struct ycc_img* image);

// takes a ycc_img struct and writes it to a binary file
// returns a non-zero value on success, 0 on failure
int write_ycc_img(char* filename, struct ycc_img* image);

// reads a PPM image stored at filename and populates image with its data
// returns a non-zero value on success, 0 on failure
int read_rgb_img(char* filename, struct rgb_img* image);

// takes a rgb_img struct and writes it to a PPM file
// returns a non-zero value on success, 0 on failure
int write_rgb_img(char* filename, struct rgb_img* image);
