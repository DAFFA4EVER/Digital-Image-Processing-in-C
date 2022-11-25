#include "includes.h"

/***************************************************/
/* Main Function                                   */
/***************************************************/
int main(int argc, char *argv[])
{
    Bitmap *inIM, *outIM;
    char inName[255]  = "lena.pgm";
    char outName[255] = "filter.pgm";
    double *rdata, *idata, *srdata, *sidata, *hfilt;
    double sigma;
    int ndata, nhalf, pel;
    int x, y;

    sigma = 30;

    printf("Loading...%s\n", inName);
    inIM = loadPgm(inName);

    /* Definition of image structure for output */
    outIM = (Bitmap*)malloc(sizeof(Bitmap));
    if (outIM == NULL) {
        fprintf(stderr, "can't allocate memory.\n");
        exit(1);
    }
    outIM->format = PGM;
    outIM->width = inIM->width;
    outIM->height = inIM->height;
    outIM->rmap = outIM->gmap = outIM->bmap = NULL;
    outIM->map = (unsigned char*)malloc(inIM->width * inIM->height * sizeof(unsigned char));
    if (outIM->map == NULL) {
        fprintf(stderr, "can't allocate memory.\n");
        exit(1);
    }

    /* setting image data for DFT */
    if (((rdata = (double *)malloc(inIM->width * inIM->height * sizeof(double))) == NULL) ||
        ((idata = (double *)malloc(inIM->width * inIM->height * sizeof(double))) == NULL)) {
        fprintf(stderr, "can't allocate memory...\n");
        exit(1);
    }
    ndata = inIM->width;
    if ((ndata != inIM->height) || (((ndata != 0) && !(ndata & (ndata - 1))) == 0)) {
        fprintf(stderr, "wrong image size (%d)...\n", ndata);
        exit(1);
    }
    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            rdata[y * ndata + x] = (double)(inIM->map[y * ndata + x]);
            idata[y * ndata + x] = 0.0;
        }
    }
    fft2d(rdata, idata, ndata, 1);

    if (((srdata = (double*)malloc(inIM->width * inIM->height * sizeof(double))) == NULL) ||
        ((sidata = (double*)malloc(inIM->width * inIM->height * sizeof(double))) == NULL) ||
        ((hfilt = (double*)malloc(inIM->width * inIM->height * sizeof(double))) == NULL)) {
        fprintf(stderr, "can't allocate memory...\n");
        exit(1);
    }
    nhalf = ndata / 2;
    for (y = 0; y < nhalf; y++) {
        for (x = 0; x < nhalf; x++) {
            srdata[(y + nhalf) * ndata + (x + nhalf)] = rdata[y * ndata + x];
            sidata[(y + nhalf) * ndata + (x + nhalf)] = idata[y * ndata + x];
        }
    }
    for (y = 0; y < nhalf; y++) {
        for (x = nhalf; x < ndata; x++) {
            srdata[(y + nhalf) * ndata + (x - nhalf)] = rdata[y * ndata + x];
            sidata[(y + nhalf) * ndata + (x - nhalf)] = idata[y * ndata + x];
        }
    }
    for (y = nhalf; y < ndata; y++) {
        for (x = 0; x < nhalf; x++) {
            srdata[(y - nhalf) * ndata + (x + nhalf)] = rdata[y * ndata + x];
            sidata[(y - nhalf) * ndata + (x + nhalf)] = idata[y * ndata + x];
        }
    }
    for (y = nhalf; y < ndata; y++) {
        for (x = nhalf; x < ndata; x++) {
            srdata[(y - nhalf) * ndata + (x - nhalf)] = rdata[y * ndata + x];
            sidata[(y - nhalf) * ndata + (x - nhalf)] = idata[y * ndata + x];
        }
    }

    /*****************/
    /*** filtering ***/
    /*****************/
    makeGaussfilt(hfilt, ndata, sigma);

    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            srdata[y * ndata + x] = hfilt[y * ndata + x] * srdata[y * ndata + x];
            sidata[y * ndata + x] = hfilt[y * ndata + x] * sidata[y * ndata + x];
        }
    }


    for (y = 0; y < nhalf; y++) {
        for (x = 0; x < nhalf; x++) {
            rdata[(y + nhalf) * ndata + (x + nhalf)] = srdata[y * ndata + x];
            idata[(y + nhalf) * ndata + (x + nhalf)] = sidata[y * ndata + x];
        }
    }
    for (y = 0; y < nhalf; y++) {
        for (x = nhalf; x < ndata; x++) {
            rdata[(y + nhalf) * ndata + (x - nhalf)] = srdata[y * ndata + x];
            idata[(y + nhalf) * ndata + (x - nhalf)] = sidata[y * ndata + x];
        }
    }
    for (y = nhalf; y < ndata; y++) {
        for (x = 0; x < nhalf; x++) {
            rdata[(y - nhalf) * ndata + (x + nhalf)] = srdata[y * ndata + x];
            idata[(y - nhalf) * ndata + (x + nhalf)] = sidata[y * ndata + x];
        }
    }
    for (y = nhalf; y < ndata; y++) {
        for (x = nhalf; x < ndata; x++) {
            rdata[(y - nhalf) * ndata + (x - nhalf)] = srdata[y * ndata + x];
            idata[(y - nhalf) * ndata + (x - nhalf)] = sidata[y * ndata + x];
        }
    }

    fft2d(rdata, idata, ndata, -1);

    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            pel = (int)(rdata[y*ndata + x] + 0.5);
            if (pel < 0) pel = 0;
            if (pel > 255) pel = 255;
            outIM->map[y * ndata + x] = (unsigned char)pel;
        }
    }

    printf("Saving...%s\n", outName);
    savePgm(outName, outIM);

    return 0;
}
