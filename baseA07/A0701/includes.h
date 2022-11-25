#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define PPM 6
#define PGM 5
#define PBM 4
#define BUFF 1024

#define RAISE(x) ((int)(x)+(((float)(x)==(int)(x))?0:1))

typedef struct _bitmap {
	char format;
	int width;
	int height;
	unsigned char* rmap;
	unsigned char* gmap;
	unsigned char* bmap;
	unsigned char* map;
} Bitmap;

#include "ppm.h"
#include "pgm.h"
#include "pbm.h"

#include "fft.h"
#include "pwrspc.h"
