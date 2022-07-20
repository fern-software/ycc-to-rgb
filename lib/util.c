#include "util.h"

#include <stdlib.h>
#include <stdio.h>

int read_ycc_img(char* filename, struct ycc_img* image){
	if(!image){
		return 0;
	}

	if(!image->y || !image->cb || !image->cr){
		return 0;
	}

	FILE* fp = fopen(filename, "r");
	if(!fp){
		return 0;
	}

	for(int i = 0; i < image->width * image->height; ++i){
		(image->y[i]) = fgetc(fp);
		if (i % 4 == 0){
			(image->cb[i / 4]) = fgetc(fp);
			(image->cr[i / 4]) = fgetc(fp);
		}
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