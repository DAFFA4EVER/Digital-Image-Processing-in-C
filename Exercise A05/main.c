#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char* argv[])
{
	Bitmap* inIM, * labelIM, * edgeIM;
	char* inName  = "sample.pbm";
	char* outName = "edge.pbm";
	int numLabel;

	printf("Loading...%s\n", inName);
	inIM = loadPbm(inName);

	/* Definition of image structure for output */
	labelIM = (Bitmap*)malloc(sizeof(Bitmap));
	edgeIM = (Bitmap*)malloc(sizeof(Bitmap));
	if (labelIM == NULL || edgeIM == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}
	labelIM->format = PGM;
	edgeIM->format = PBM;
	labelIM->width  = edgeIM->width  = inIM->width;
	labelIM->height = edgeIM->height = inIM->height;
	labelIM->rmap = labelIM->gmap = labelIM->bmap = labelIM->map = NULL;
	labelIM->map = (unsigned char*)malloc(inIM->width * inIM->height * sizeof(unsigned char));
	edgeIM->map = (unsigned char*)malloc(inIM->width * inIM->height * sizeof(unsigned char));
	if (labelIM->map == NULL || edgeIM->map == NULL) {
		fprintf(stderr, "can't allocate memory.\n");
		exit(1);
	}

	/* labeling */
	numLabel = labeling(inIM, labelIM);
	printf("label number = %d\n", numLabel);

	/* contour detection */
	detect_contour(labelIM, numLabel, edgeIM);

	printf("Saving...%s\n", outName);
	savePbm(outName, edgeIM);

	return 0;
}
