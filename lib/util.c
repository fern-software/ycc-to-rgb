#include "util.h"

#include <stdlib.h>
#include <stdio.h>

int read_ycc_img(char* filename, struct ycc_img* image){
	image = malloc(sizeof(struct ycc_img));
	if(!image){
		return 0;
	}

	// TODO: remove the hardcoding
	image->width = 1024;
	image->height = 1024;

	image->data = malloc(1024 * 1024);
	if(!image->data){
		return 0;
	}

	FILE* fp = fopen(filename, "r");
	if(!fp){
		return 0;
	}

	for(int i = 0; i < 1024 * 1024; ++i){
		image->data->y = fgetc(fp);
		image->data->cb = fgetc(fp);
		image->data->cr = fgetc(fp);
	}
	
	fclose(fp);
	return 1;
}
