// Converts a YCbCr image given in a custom file format into an RGB image given as a PPM file
// Prints benchmarks for the three main functions used by the program in ms.

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <time.h>

#include "util.h"
#include "conversion.h"

int main(int argc, char **argv){
	int err;

	struct ycc_img in_img;
	struct rgb_img out_img;

	clock_t start_read;
	clock_t end_read;
	clock_t start_convert;
	clock_t end_convert;
	clock_t start_write;
	clock_t end_write;
	
	if(argc != 3){
		fprintf(stderr, "ycc input file name and ppm output file name expected.\n");
		exit(EXIT_FAILURE);
	}

	start_read = clock();
	err = read_ycc_img(argv[1], &in_img);
	end_read = clock();

	if(!err){
		error(EXIT_FAILURE, errno, "reading image failed");
	}

	start_convert = clock();
	ycc_to_rgb(&in_img, &out_img);
	end_convert = clock();

	free(in_img.data);
	
	start_write = clock();
	err = write_rgb_img(argv[2], &out_img);
	end_write = clock();

	if(!err){
		error(EXIT_FAILURE, errno, "writing image failed");
	}

	free(out_img.data);

	printf("CPU time used by reading image: %ldms\n", (end_read - start_read) / (CLOCKS_PER_SEC / 1000));
	printf("CPU time used by converting image: %ldms\n", (end_convert - start_convert) / (CLOCKS_PER_SEC / 1000));
	printf("CPU time used by writing image: %ldms\n", (end_write - start_write) / (CLOCKS_PER_SEC / 1000));
	
	return 0;
}
