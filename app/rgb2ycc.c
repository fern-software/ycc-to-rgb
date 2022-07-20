// Converts an RGB image given as a PPM file into a YCbCr image given in a custom file format

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#include "util.h"
#include "conversion.h"

int main(int argc, char **argv){
	int err;

	struct rgb_img in_img;
	struct ycc_img out_img;
	
	if(argc != 3){
		fprintf(stderr, "ppm input file name and ycc output file name expected.\n");
		exit(EXIT_FAILURE);
	}

	err = read_rgb_img(argv[1], &in_img);
	if(!err){
		error(EXIT_FAILURE, errno, "reading image failed");
	}

	rgb_to_ycc(&in_img, &out_img);
	free(in_img.data);

	err = write_ycc_img(argv[2], &out_img);
	if(!err){
		error(EXIT_FAILURE, errno, "writing image failed");
	}

	free(out_img.data);
	
	return 0;
}
