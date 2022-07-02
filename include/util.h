#pragma once

#include <stdint.h>

struct ycc_pixel {
	uint8_t y;
	uint8_t cb;
	uint8_t cr;
};

struct ycc_img {
	struct ycc_pixel* data;
	unsigned int width;
	unsigned int height;
};

// reads a YCC image stored at filename and sets image to point to where the data is stored
// returns a non-zero value on success, 0 on failure
int read_ycc_img(char* filename, struct ycc_img* image);
