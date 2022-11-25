#include "includes.h"

#define FFT_MAX 2048

int fft2d(double* rdata, double* idata, int ndata, int opt)
{
	double re[FFT_MAX], im[FFT_MAX];
	int i, j;

	for (j = 0; j < ndata; j++) {
		for (i = 0; i < ndata; i++) {
			re[i] = rdata[j * ndata + i];
			im[i] = idata[j * ndata + i];
		}
		fft1d(re, im, ndata, opt);
		for (i = 0; i < ndata; i++) {
			rdata[j * ndata + i] = re[i];
			idata[j * ndata + i] = im[i];
		}
	}
	for (j = 0; j < ndata; j++) {
		for (i = 0; i < ndata; i++) {
			re[i] = rdata[i * ndata + j];
			im[i] = idata[i * ndata + j];
		}
		fft1d(re, im, ndata, opt);
		for (i = 0; i < ndata; i++) {
			rdata[i * ndata + j] = re[i];
			idata[i * ndata + j] = im[i];
		}
	}

	return 0;
}

int fft1d(double* re, double* im, int ndata, int opt)
{
	double rbuf[FFT_MAX], ibuf[FFT_MAX];
	double rnew[FFT_MAX], inew[FFT_MAX];
	double uangle, sangle, angle, rtmp, itmp;
	int power, ndft, dft, nptr, ptr, offset, half;
	int nout, nin1, nin2, n, i, j, k;

	for (i = 0; i < FFT_MAX; i++) rbuf[i] = ibuf[i] = rnew[i] = inew[i] = 0.0;

	if (opt == -1) {
		for (i = 0; i < ndata; i++) {
			re[i] = re[i] / ndata;
			im[i] = -im[i] / ndata;
		}
	}
	power = 0;
	n = ndata;
	while (n != 1) {
		power++;
		n = n / 2;
	}

	/*** data initialization ***/
	dft = ndata;
	for (i = 1; i < power; i++) {
		nptr = offset = 0;
		while (nptr < ndata) {
			ptr = 0;
			while (ptr < dft) {
				rbuf[nptr] = re[offset + ptr];
				ibuf[nptr] = im[offset + ptr];
				nptr++;
				ptr += 2;
				if (ptr == dft) ptr = 1;
			}
			offset = offset + dft;
		}
		for (j = 0; j < ndata; j++) {
			re[j] = rbuf[j];
			im[j] = ibuf[j];
		}
		dft = dft / 2;
	}

	/*** main part ***/
	uangle = 2.0 * M_PI / ndata;
	dft = 2;
	for (i = 0; i < power; i++) {
		ndft = ndata / dft;
		sangle = uangle * ndft;
		half = dft / 2;
		for (j = 0; j < ndft; j++) {
			angle = 0.0;
			for (k = 0; k < dft; k++) {
				nout = j * dft + k;
				if (k < half) {
					nin1 = nout;
					nin2 = nin1 + half;
				} else {
					nin2 = nout;
					nin1 = nout - half;
				}
				rtmp = re[nin2];
				itmp = im[nin2];
				rnew[nout] = re[nin1] + rtmp * cos(angle) + itmp * sin(angle);
				inew[nout] = im[nin1] + itmp * cos(angle) - rtmp * sin(angle);
				angle = angle + sangle;
			}
		}
		for (j = 0; j < ndata; j++) {
			re[j] = rnew[j];
			im[j] = inew[j];
		}
		dft = dft * 2;
	}
	if (opt == -1) {
		for (j = 0; j < ndata; j++) {
			im[j] = -im[j];
		}
	}

	return 0;
}