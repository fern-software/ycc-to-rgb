#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#include "util.h"

int main(int argc, char **argv){
	int err;
	struct ycc_img* img;
	
	if(argc != 2){
		fprintf(stderr, "YCC file expected.\n");
		exit(EXIT_FAILURE);
	}

	err = read_ycc_img(argv[1], img);
	if(!err){
		error(EXIT_FAILURE, errno, "reading image failed");
	}

	// TODO: remove this and call the conversion function
	struct rgb_img* rimg = malloc(sizeof(struct rgb_img));
	rimg->data = malloc(1024 * 1024 * sizeof(struct rgb_pixel));
	rimg->height = IMAGE_HEIGHT;
	rimg->width = IMAGE_WIDTH;
	
	err = write_rgb_img("result.ppm", rimg);
	if(!err){
		error(EXIT_FAILURE, errno, "writing image failed");
	}
	
	return 0;
}
