#pragma once

#include <stdint.h>

#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024

struct ycc_img {
	uint8_t *y;
	uint8_t *cb;
	uint8_t *cr;
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

// Returns the smaller of a,b. If a==b, returns a.
int min(int a, int b);

// Returns the larger of a,b. If a==b, returns a.
int max(int a, int b);

// reads a YCC image stored at filename and populates image with its data
// returns a non-zero value on success, 0 on failure
// note: allocates memory for image
int read_ycc_img(char* filename, struct ycc_img* image);

// takes a rgb_img struct and writes it to a PPM file
// returns a non-zero value on success, 0 on failure
int write_rgb_img(char* filename, struct rgb_img* image);
