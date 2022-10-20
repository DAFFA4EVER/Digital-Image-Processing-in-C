#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char* argv[])
{
	Bitmap* inIM, * outIM;
	char* inName = "cat001.pgm";
	char* outName = "cat001_sauvola.pbm";

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

	sauvolaBinalization(inIM, outIM);

	printf("Saving...%s\n", outName);
	savePbm(outName, outIM);

	return 0;
}
