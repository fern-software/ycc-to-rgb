#include "util.h"

#include <stdlib.h>
#include <stdio.h>

// at some point this could be removed to instead read this data from the file
#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024

int read_ycc_img(char* filename, struct ycc_img* image){
	image = malloc(sizeof(struct ycc_img));
	if(!image){
		return 0;
	}

	image->width = IMAGE_WIDTH;
	image->height = IMAGE_HEIGHT;

	image->data = malloc(image->width * image->height);
	if(!image->data){
		return 0;
	}

	FILE* fp = fopen(filename, "r");
	if(!fp){
		return 0;
	}

	for(int i = 0; i < image->width * image->height; ++i){
		image->data->y = fgetc(fp);
		image->data->cb = fgetc(fp);
		image->data->cr = fgetc(fp);
	}
	
	fclose(fp);
	return 1;
}
