#include "includes.h"

int makeGaussfilt(double* hfilt, int ndata, double sigma)
{
    double max, min, p, xx, yy;
    int x, y;
    int nhalf = ndata / 2;

    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            hfilt[y * ndata + x] = 0.0;
        }
    }
    max = DBL_MIN;
    min = DBL_MAX;
    for (y = 0, yy = -nhalf; y < ndata; y++, yy++) {
        for (x = 0, xx = -nhalf; x < ndata; x++, xx++) {
	        /*************/ 
            p =  (1/(2*M_PI*(sigma*sigma))) * exp((-(xx*xx + yy*yy))/(2*(sigma*sigma)));
            /*************/
            hfilt[y * ndata + x] = p;
            if (max < p) max = p;
            if (min > p) min = p;
        }
    }
    for (y = 0; y < ndata; y++) {
        for (x = 0; x < ndata; x++) {
            hfilt[y * ndata + x] = (hfilt[y * ndata + x] - min) / (max - min);
        }
    }

    return 0;
}
