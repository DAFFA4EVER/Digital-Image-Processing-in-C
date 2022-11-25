#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char *argv[])
{
    Bitmap *inIM, *outIM;
    char inName[255]  = "lena.pgm";
    char outName[255] = "pwrspc.pgm";
    double *rdata, *idata;
    int x, y, ndata;

    printf("Loading...%s\n", inName);
    inIM = loadPgm(inName);

    /* setting image data*/
    ndata = inIM->width;
    if ((ndata != inIM->height) || (((ndata != 0) && !(ndata & (ndata - 1))) == 0)) {
        fprintf(stderr, "wrong image size (%d)...\n", ndata);
        exit(1);
    }
    if (((rdata = (double*)malloc(inIM->width * inIM->height * sizeof(double))) == NULL) ||
        ((idata = (double*)malloc(inIM->width * inIM->height * sizeof(double))) == NULL)) {
        fprintf(stderr, "can't allocate memory...\n");
        exit(1);
    }
    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            rdata[y * ndata + x] = (double)(inIM->map[y * ndata + x]);
            idata[y * ndata + x] = 0.0;
        }
    }

    /* fourier transformation*/
    fft2d(rdata, idata, ndata, 1);

    outIM = makePwrspc(rdata, idata, ndata);

    printf("Saving...%s\n", outName);
    savePgm(outName, outIM);

    return 0;
}
