#include "includes.h"

static int ex[8] = { -1, 0, 1,-1, 1,-1, 0, 1 };
static int ey[8] = { -1,-1,-1, 0, 0, 1, 1, 1 };

int dilationMorph(Bitmap* inIM, Bitmap* outIM)
{
	int i, x, y;

	/* check */
	if ((inIM->format != outIM->format) || (inIM->width != outIM->width) || (inIM->height != outIM->height)) {
		return -1;
	}

	/* copy */
	for (y = 0; y < inIM->height; y++)
		for (x = 0; x < inIM->width; x++)
			outIM->map[y * outIM->width + x] = inIM->map[y * inIM->width + x];

	/* dilation */
	for (y = 1; y < inIM->height - 1; y++) {
		for (x = 1; x < inIM->width - 1; x++) {
		/******************/
			if(inIM->map[y * inIM->width + x] == 1){
				for(i = 0; i < 8; i++){
					outIM->map[(y+ey[i]) * outIM->width + (x+ex[i])] = 1;
				}
			}
		/******************/
		}
	}

	return 0;
}

int erosionMorph(Bitmap* inIM, Bitmap* outIM)
{
	int i, x, y;

	/* check */
	if ((inIM->format != outIM->format) || (inIM->width != outIM->width) || (inIM->height != outIM->height)) {
		return -1;
	}

	/* copy */
	for (y = 0; y < inIM->height; y++)
		for (x = 0; x < inIM->width; x++)
			outIM->map[y * outIM->width + x] = inIM->map[y * inIM->width + x];

	/* erosion */
	for (y = 1; y < inIM->height - 1; y++) {
		for (x = 1; x < inIM->width - 1; x++) {
		/******************/
			if(inIM->map[y * inIM->width + x] == 0){
				for(i = 0; i < 8; i++){
					outIM->map[(y+ey[i]) * outIM->width + (x+ex[i])] = 0;
				}
			}
		/******************/
		}
	}

	return 0;
}

int openingMorph(Bitmap* inIM, Bitmap* outIM)
{
	Bitmap* tmpIM;

	/* Definition of image structure for output */
	tmpIM = (Bitmap*)malloc(sizeof(Bitmap));
	if (tmpIM == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}
	tmpIM->format = inIM->format;
	tmpIM->width = inIM->width;
	tmpIM->height = inIM->height;
	tmpIM->rmap = tmpIM->gmap = tmpIM->bmap = tmpIM->map = NULL;
	tmpIM->map = (unsigned char*)malloc(inIM->width * inIM->height * sizeof(unsigned char));
	if (tmpIM->map == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

	/**************/
	erosionMorph(inIM, tmpIM);
	dilationMorph(tmpIM, outIM);
	/**************/

	free(tmpIM->map);

	return 0;
}

int closingMorph(Bitmap* inIM, Bitmap* outIM)
{
	Bitmap* tmpIM;

	/* Definition of image structure for output */
	tmpIM = (Bitmap*)malloc(sizeof(Bitmap));
	if (tmpIM == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}
	tmpIM->format = inIM->format;
	tmpIM->width = inIM->width;
	tmpIM->height = inIM->height;
	tmpIM->rmap = tmpIM->gmap = tmpIM->bmap = tmpIM->map = NULL;
	tmpIM->map = (unsigned char*)malloc(inIM->width * inIM->height * sizeof(unsigned char));
	if (tmpIM->map == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

	/**************/
	dilationMorph(inIM, tmpIM);
	erosionMorph(tmpIM, outIM);
	/**************/

	free(tmpIM->map);

	return 0;
}