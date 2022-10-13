#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char* argv[])
{
	Bitmap* inIM, * outIM;
	char* inName  = "cat001.ppm";
	char* outName = "output.ppm";
	char* gray_name = "cat_gray.pgm";
	char* pseudoColor_name = "cat_colorize.ppm";
	int x, y;

	printf("Loading...%s\n", inName);
	inIM = loadPpm(inName);

	/* Definition of image structure for output */
	outIM = (Bitmap*)malloc(sizeof(Bitmap));
	if (outIM == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}
	outIM->format = inIM->format;
	outIM->width  = inIM->width;
	outIM->height = inIM->height;
	outIM->rmap = outIM->gmap = outIM->bmap = outIM->map = NULL;
	outIM->rmap = (unsigned char*)malloc(outIM->width * outIM->height * sizeof(unsigned char));
	outIM->gmap = (unsigned char*)malloc(outIM->width * outIM->height * sizeof(unsigned char));
	outIM->bmap = (unsigned char*)malloc(outIM->width * outIM->height * sizeof(unsigned char));
	if (outIM->rmap == NULL || outIM->gmap == NULL|| outIM->bmap == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

	/* Copying */
	for (y = 0; y < inIM->height; y++) {
		for (x = 0; x < inIM->width; x++) {
			outIM->rmap[y * outIM->width + x] = inIM->rmap[y * inIM->width + x];
			outIM->gmap[y * outIM->width + x] = inIM->gmap[y * inIM->width + x];
			outIM->bmap[y * outIM->width + x] = inIM->bmap[y * inIM->width + x];
		}
	}

	printf("Saving...%s\n", outName);
	savePpm(outName, outIM);

	to_gray(outIM, gray_name);
	to_colorize(gray_name, pseudoColor_name);

	
	return 0;
}
