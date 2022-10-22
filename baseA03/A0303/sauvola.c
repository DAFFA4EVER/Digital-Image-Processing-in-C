#include "includes.h"

#define N 15

int sauvolaBinalization(Bitmap* im, Bitmap* om)
{
	double th;
	unsigned char tmp[N * N];
	int n;
	int x, y, i, j;

	n = (int)(N / 2);
	for (y = 0; y < im->height; y++) {
		for (x = 0; x < im->width; x++) {
			if ((y - n) < 0 || (y + n) > im->height ||
				(x - n) < 0 || (x + n) > im->width) {
				om->map[y * im->width + x] = 1;
			} else {
				for (j = 0; j < N; j++) {
					for (i = 0; i < N; i++) {
						tmp[j * N + i] = im->map[(y - n + j) * im->width + (x - n + i)];
					}
				}
				th = thSauvola(tmp);

				if (im->map[y * im->width + x] <= th)
					om->map[y * im->width + x] = 1;
				else
					om->map[y * im->width + x] = 0;
			}
		}
	}

	return 0;
}

int thSauvola(unsigned char* img)
{
	/***********/
	double m = 0, var = 0, th = 0, k = 0.05, R =128, n = N * N;

	//mean
	for(int x = 0; x < n; x++){
		m = m + img[x];
	}
	m = m / n;

	//var
	for(int i = 0; i < n; i++){
		var = var + pow((img[i]-m),2);
	}
	var = var / n;
	th = m * (1-k * (1-sqrt(var)/R));
	/***********/
	return th;
}