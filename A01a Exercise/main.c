#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char* argv[])
{
	Bitmap* inIM, * outIM;
	char* inName  = "cat001.ppm";
	char* outName = "output.ppm";
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
	int p = 0;
	for (y = 0; y < inIM->height; y++) {
		for (x = 0; x < inIM->width; x++) {
			outIM->rmap[y * outIM->width + x] = inIM->rmap[y * inIM->width + x];
			outIM->gmap[y * outIM->width + x] = inIM->gmap[y * inIM->width + x];
			outIM->bmap[y * outIM->width + x] = inIM->bmap[y * inIM->width + x];
            p++;
        }
	}
	printf("Saving...%s\n", outName);
	savePpm(outName, outIM);

    /* My Code */
    float mean_result[3] = {0,0,0}, variance_result[3] = {0,0,0};
    find_mean(outIM, mean_result);
    find_variance(outIM, variance_result, mean_result);

    printf("\nRed: mean = %.2f, variance = %.2f\n", mean_result[0], variance_result[0]);
    printf("\nGreen: mean = %.2f, variance = %.2f\n", mean_result[1], variance_result[1]);
    printf("\nBlue: mean = %.2f, variance = %.2f\n", mean_result[2], variance_result[2]);

	return 0;
}

/* Muhammad Daffa Khairi - 2246176007 */
