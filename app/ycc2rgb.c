#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#include "util.h"
#include "conversion.h"

int main(int argc, char **argv){
	int err;

	// Allocate memory
	struct ycc_img* in_img = malloc(sizeof(struct ycc_img));
	in_img->width = IMAGE_WIDTH;
	in_img->height = IMAGE_HEIGHT;

	in_img->y = malloc(in_img->width * in_img->height * sizeof(uint8_t));
	in_img->cb = malloc((in_img->width * in_img->height * sizeof(uint8_t)) / 4);
	in_img->cr = malloc((in_img->width * in_img->height * sizeof(uint8_t)) / 4);

	struct rgb_img* out_img = malloc(sizeof(struct rgb_img));
	
	if(argc != 3){
		fprintf(stderr, "ycc input file name and ppm output file name expected.\n");
		exit(EXIT_FAILURE);
	}

	err = read_ycc_img(argv[1], in_img);
	if(!err){
		error(EXIT_FAILURE, errno, "reading image failed");
	}

	ycc_to_rgb(in_img, out_img);
	
	err = write_rgb_img(argv[2], out_img);
	if(!err){
		error(EXIT_FAILURE, errno, "writing image failed");
	}

	
	free(in_img->y);
	free(in_img->cr);
	free(in_img->cb);
	
	free(out_img->data);
	free(in_img);
	free(out_img);
	
	return 0;
}
