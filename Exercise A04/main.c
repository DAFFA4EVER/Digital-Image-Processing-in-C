#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char* argv[])
{
	Bitmap* inIM, * outIM;
	char* inName  = "time.pbm";
	char* outName = "morph.pbm";

	printf("Loading...%s\n", inName);
	inIM = loadPbm(inName);

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
	outIM->map = (unsigned char*)malloc(outIM->width * outIM->height * sizeof(unsigned char));
	if (outIM->map == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

	/* opening */
	openingMorph(inIM, outIM);
	/* closing */
	closingMorph(outIM, inIM);

	printf("Saving...%s\n", outName);
	savePbm(outName, inIM);

	return 0;
}
