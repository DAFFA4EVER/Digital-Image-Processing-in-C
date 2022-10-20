#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char* argv[])
{
	Bitmap* inIM, * outIM;
	char* inName = "cat001.pgm";
	char* outName = "cat001_otsu.pbm";
	int th =128;
	int x, y;

	printf("Loading...%s\n", inName);
	inIM = loadPgm(inName);

	/* Definition of image structure for output */
	outIM = (Bitmap*)malloc(sizeof(Bitmap));
	if (outIM == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}
	outIM->format = PBM;
	outIM->width  = inIM->width;
	outIM->height = inIM->height;
	outIM->rmap = outIM->gmap = outIM->bmap = outIM->map = NULL;
	outIM->map = (unsigned char*)malloc(inIM->width * inIM->height * sizeof(unsigned char));
	if (outIM->map == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

	th = otsuBinalization(inIM);
	printf("threshold level = %d\n", th);

	/* Thresholding */
	for (y = 0; y < inIM->height; y++) {
		for (x = 0; x < inIM->width; x++) {
			if (inIM->map[y * inIM->width + x] <= th)
				outIM->map[y * inIM->width + x] = 1;
			else
				outIM->map[y * inIM->width + x] = 0;
		}
	}

	printf("Saving...%s\n", outName);
	savePbm(outName, outIM);

	return 0;
}
