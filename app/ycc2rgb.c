#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#include "util.h"
#include "conversion.h"

int main(int argc, char **argv){
	int err;
	struct ycc_img* img = malloc(sizeof(struct ycc_img));
	struct rgb_img* out_img = malloc(sizeof(struct rgb_img));
	
	if(argc != 2){
		fprintf(stderr, "YCC file expected.\n");
		exit(EXIT_FAILURE);
	}

	err = read_ycc_img(argv[1], img);
	if(!err){
		error(EXIT_FAILURE, errno, "reading image failed");
	}

	ycc_to_rgb(&img, &out_img);
	
	err = write_rgb_img("result.ppm", out_img);
	if(!err){
		error(EXIT_FAILURE, errno, "writing image failed");
	}
	
	return 0;
}
