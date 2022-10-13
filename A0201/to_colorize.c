#include "includes.h"

void to_colorize(char * gray_name, char* pseudoColor_name){
    int x, y;
	Bitmap * colorize_img, * grayIM;

	grayIM = loadPgm(gray_name);
	/* Definition of image structure for output */
	colorize_img = (Bitmap*)malloc(sizeof(Bitmap));
	colorize_img->format = PPM;
	colorize_img->height = grayIM->height;
	colorize_img->width = grayIM->width;

	colorize_img->rmap = colorize_img->gmap = colorize_img->bmap = colorize_img->map = NULL;
	colorize_img->rmap = (unsigned char*)malloc(colorize_img->width * colorize_img->height * sizeof(unsigned char));
	colorize_img->gmap = (unsigned char*)malloc(colorize_img->width * colorize_img->height * sizeof(unsigned char));
	colorize_img->bmap = (unsigned char*)malloc(colorize_img->width * colorize_img->height * sizeof(unsigned char));
	colorize_img->map = (unsigned char*)malloc(colorize_img->width * colorize_img->height * sizeof(unsigned char));
	if (colorize_img->rmap == NULL || colorize_img->gmap == NULL|| colorize_img->bmap == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}
	for (y = 0; y < grayIM->height; y++) {
		for (x = 0; x < grayIM->width; x++) {
			if(grayIM->map[y * grayIM->width + x] >= 0 && grayIM->map[y * grayIM->width + x] <= 63){
				colorize_img->rmap[y * colorize_img->width + x] = 0;
				colorize_img->gmap[y * colorize_img->width + x] = 4 * (grayIM->map[y * grayIM->width + x] - 1) - 1;
				colorize_img->bmap[y * colorize_img->width + x] = 255;
			
			}else if(grayIM->map[y * grayIM->width + x] >= 64 && grayIM->map[y * grayIM->width + x] <= 127){
				colorize_img->rmap[y * colorize_img->width + x] = 0;
				colorize_img->gmap[y * colorize_img->width + x] = 255;
				colorize_img->bmap[y * colorize_img->width + x] = 256 - 4 * (grayIM->map[y * grayIM->width + x] - 63);
			
			}else if(grayIM->map[y * grayIM->width + x] >= 128 && grayIM->map[y * grayIM->width + x] <= 191){ 
				colorize_img->rmap[y * colorize_img->width + x] = 4 * (grayIM->map[y * grayIM->width + x] - 127) - 1;
				colorize_img->gmap[y * colorize_img->width + x] = 255;
				colorize_img->bmap[y * colorize_img->width + x] = 0;
			
			}else if(grayIM->map[y * grayIM->width + x] >= 192 && grayIM->map[y * grayIM->width + x] <= 255){
				colorize_img->rmap[y * colorize_img->width + x] = 255;
				colorize_img->gmap[y * colorize_img->width + x] = 256 - 4 * (grayIM->map[y * grayIM->width + x] - 191);
				colorize_img->bmap[y * colorize_img->width + x] = 0;
			
			}
		}
	}
	savePpm(pseudoColor_name, colorize_img);
	printf("\nPseudoColor image was saved as : %s", pseudoColor_name);
}