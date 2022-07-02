#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#include "util.h"

int main(int argc, char **argv){
	int err;
	struct ycc_img* img;
	
	if(argc != 2){
		fprintf(stderr, "YCC file name expected.\n");
		exit(EXIT_FAILURE);
	}


	err = read_ycc_img(argv[1], img);
	if(!err){
		error(EXIT_FAILURE, errno, "reading image failed");
	}
	
	return 0;
}
