#include "includes.h"

int otsuBinalization(Bitmap* bm)
{
	float m1, m2, evl, maxevl;
	int np1, np2;
	int maxpel, minpel, th;
	int x, y, k;

	/* Obtaining of maximum/minimum intensity */
	maxpel = -1; minpel = 300;
	for (y = 0; y < bm->height; y++) {
		for (x = 0; x < bm->width; x++) {
			if (bm->map[y * bm->width + x] > maxpel) maxpel = bm->map[y * bm->width + x];
			if (bm->map[y * bm->width + x] < minpel) minpel = bm->map[y * bm->width + x];
		}
	}

	maxevl = -1; th = -1;
	for (k = minpel; k < maxpel; k++) {

		m1 = m2 = 0.0;
		np1 = np2 = 0;
		for (y = 0; y < bm->height; y++) {
			for (x = 0; x < bm->width; x++) {
				if (bm->map[y * bm->width + x] <= k) {
					m1 += bm->map[y * bm->width + x];
					np1++;
				}
				else {
					m2 += bm->map[y * bm->width + x];
					np2++;
				}
			}
		}
		m1 /= np1;
		m2 /= np2;
		/**************************************/
		evl = np1 * np2 * ((m1-m2)*(m1-m2));
        /**************************************/
		if (evl > maxevl) {
			maxevl = evl;
			th = k;
		}
	}

	return th;
}
