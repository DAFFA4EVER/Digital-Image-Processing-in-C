#include "includes.h"

Bitmap* makePwrspc(double* rdata, double* idata, int ndata)
{
    Bitmap* pwrIM;
    double* pdata, * sdata;
    double fmin, fmax, pel;
    int x, y, nhalf;

    pwrIM = (Bitmap*)malloc(sizeof(Bitmap));
    if (pwrIM == NULL) {
        fprintf(stderr, "can't allocate memory.\n");
        exit(1);
    }
    pwrIM->format = PGM;
    pwrIM->width = ndata;
    pwrIM->height = ndata;
    pwrIM->rmap = pwrIM->gmap = pwrIM->bmap = NULL;
    pwrIM->map = (unsigned char*)malloc(pwrIM->width * pwrIM->height * sizeof(unsigned char));
    if (pwrIM->map == NULL) {
        fprintf(stderr, "can't allocate memory.\n");
        exit(1);
    }

    if (((pdata = (double*)malloc(pwrIM->width * pwrIM->height * sizeof(double))) == NULL) ||
        ((sdata = (double*)malloc(pwrIM->width * pwrIM->height * sizeof(double))) == NULL)) {
        fprintf(stderr, "can't allocate memory...\n");
        exit(1);
    }
    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
	    /* power spectrum */
	    /************************************************************************/
            pdata[y * ndata + x] = log10(pow(rdata[y * ndata + x],2) + pow(idata[y * ndata + x],2));
        /************************************************************************/
        }
    }
    nhalf = ndata / 2;
    for (y = 0; y < nhalf; y++) {
        for (x = 0; x < nhalf; x++) {
            sdata[(y + nhalf) * ndata + (x + nhalf)] = pdata[y * ndata + x];
        }
    }
    for (y = 0; y < nhalf; y++) {
        for (x = nhalf; x < ndata; x++) {
            sdata[(y + nhalf) * ndata + (x - nhalf)] = pdata[y * ndata + x];
        }
    }
    for (y = nhalf; y < ndata; y++) {
        for (x = 0; x < nhalf; x++) {
            sdata[(y - nhalf) * ndata + (x + nhalf)] = pdata[y * ndata + x];
        }
    }
    for (y = nhalf; y < ndata; y++) {
        for (x = nhalf; x < ndata; x++) {
            sdata[(y - nhalf) * ndata + (x - nhalf)] = pdata[y * ndata + x];
        }
    }
    fmin = DBL_MAX;
    fmax = 0.0;
    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            if (sdata[y * ndata + x] < fmin) fmin = sdata[y * ndata + x];
            if (sdata[y * ndata + x] > fmax) fmax = sdata[y * ndata + x];
        }
    }

    printf("min = %f, max = %f\n", fmin, fmax);
    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            pel = (int)(255.0 * (sdata[y * ndata + x] - fmin) / (fmax - fmin));
            if (pel < 0) pel = 0;
            if (pel > 255) pel = 255;
            pwrIM->map[y * ndata + x] = (unsigned char)pel;
        }
    }

    free(sdata);
    free(pdata);

	return pwrIM;
}
