#include "util.h"

#include <stdlib.h>
#include <stdio.h>

int read_ycc_img(char* filename, struct ycc_img* image){
	if(!image){
		return 0;
	}

	image->width = IMAGE_WIDTH;
	image->height = IMAGE_HEIGHT;

	image->data = malloc(image->width * image->height * sizeof(struct ycc_pixel));
	if(!image->data){
		return 0;
	}

	FILE* fp = fopen(filename, "r");
	if(!fp){
		return 0;
	}

	for(int i = 0; i < image->width * image->height; ++i){
		(image->data[i]).y = fgetc(fp);
		(image->data[i]).cb = fgetc(fp);
		(image->data[i]).cr = fgetc(fp);
	}
	
	fclose(fp);
	return 1;
}

int write_rgb_img(char* filename, struct rgb_img* image){
	FILE *fp = fopen(filename, "wb");
	if(!fp){
		return 0;
	}

	fprintf(fp, "P6\n%d %d\n255\n", image->width, image->height);
	for(int i = 0; i < image->width * image->height; ++i){
		fputc((image->data[i]).r, fp);
		fputc((image->data[i]).g, fp);
		fputc((image->data[i]).b, fp);
	}

	fclose(fp);

	return 1;
}

int min(int a, int b){
	if(a <= b){
		return a;
	}
	return b;
}

int max(int a, int b){
	if(a >= b){
		return a;
	}
	return b;
}