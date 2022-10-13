#include "includes.h"

void to_gray(Bitmap* img, char * gray_name){
	int x, y;
	Bitmap * gray_img;
	/* Definition of image structure for output */
	gray_img = (Bitmap*)malloc(sizeof(Bitmap));

	gray_img->format = PGM;
	gray_img->height = img->height;
	gray_img->width = img->width;

	gray_img->rmap = gray_img->gmap = gray_img->bmap = gray_img->map = NULL;
	gray_img->rmap = (unsigned char*)malloc(gray_img->width * gray_img->height * sizeof(unsigned char));
	gray_img->gmap = (unsigned char*)malloc(gray_img->width * gray_img->height * sizeof(unsigned char));
	gray_img->bmap = (unsigned char*)malloc(gray_img->width * gray_img->height * sizeof(unsigned char));
	gray_img->map = (unsigned char*)malloc(gray_img->width * gray_img->height * sizeof(unsigned char));
	if (gray_img->rmap == NULL || gray_img->gmap == NULL|| gray_img->bmap == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

    for (y = 0; y < img->height; y++) {
		for (x = 0; x < img->width; x++) {
			gray_img->map[y * gray_img->width + x] = img->rmap[y * img->width + x] * 0.2126 + img->gmap[y * img->width + x] * 0.7152 + img->bmap[y * img->width + x] * 0.0722;
        }
	}

	savePgm(gray_name, gray_img);
	printf("\nGrayscale image was saved as : %s", gray_name);
}
