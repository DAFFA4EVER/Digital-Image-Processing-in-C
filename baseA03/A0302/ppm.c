#include "includes.h"

/***************************************************/
/* Loading of PPM                                  */
/***************************************************/
Bitmap* loadPpm(char* name)
{
	FILE* fp;
	Bitmap* bmp;
	char buf[BUFF];
	unsigned char* tmp;
	int i, j, x, y, cnt;


	if ((fp = fopen(name, "rb")) == NULL) {
		fprintf(stderr, "can't open file (%s)\n", name);
		exit(1);
	}
	if (fgets(buf, BUFF, fp) == NULL) {
		fprintf(stderr, "wrong ppm header\n");
		exit(1);
	}
	if (strncmp(buf, "P6", 2)) {
		fprintf(stderr, "wrong ppm header\n");
		exit(1);
	}
	do {
		if (fgets(buf, BUFF, fp) == NULL) {
			fprintf(stderr, "wrong ppm header\n");
			exit(1);
		}
	} while (buf[0] == 0x23);
	sscanf(buf, "%d %d", &x, &y);
	do {
		fgets(buf, 255, fp);
	} while (buf[0] == 0x23);
	if ((tmp = (unsigned char*)malloc(3 * x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	if (fread(tmp, sizeof(char), 3 * x * y, fp) != 3 * x * y) {
		fprintf(stderr, "can't read image data\n");
		exit(1);
	}
	fclose(fp);

	if ((bmp = (Bitmap*)malloc(sizeof(Bitmap))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	bmp->format = PPM;
	bmp->width = x;
	bmp->height = y;
	if ((bmp->rmap = (unsigned char*)malloc(x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	if ((bmp->gmap = (unsigned char*)malloc(x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	if ((bmp->bmap = (unsigned char*)malloc(x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	bmp->map = NULL;
	cnt = 0;
	for (j = 0; j < y; j++) {
		for (i = 0; i < x; i++) {
			bmp->rmap[j * x + i] = tmp[cnt++];
			bmp->gmap[j * x + i] = tmp[cnt++];
			bmp->bmap[j * x + i] = tmp[cnt++];
		}
	}
	free(tmp);

	return bmp;
}

/***************************************************/
/* Saving of PPM                                   */
/***************************************************/
void savePpm(char* name, Bitmap* bmp)
{
	FILE* fp;
	unsigned char* tmp;
	int i, j, cnt;

	if (bmp->format != PPM) {
		fprintf(stderr, "wrong format\n");
		exit(1);
	}
	if ((fp = fopen(name, "wb")) == NULL) {
		fprintf(stderr, "can't open file (%s)\n", name);
		exit(1);
	}
	fprintf(fp, "P6\n%d %d\n255\n", bmp->width, bmp->height);
	if ((tmp = (unsigned char*)malloc(3 * bmp->width * bmp->height * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	cnt = 0;
	for (j = 0; j < bmp->height; j++) {
		for (i = 0; i < bmp->width; i++) {
			tmp[cnt++] = bmp->rmap[j * bmp->width + i];
			tmp[cnt++] = bmp->gmap[j * bmp->width + i];
			tmp[cnt++] = bmp->bmap[j * bmp->width + i];
		}
	}
	if (fwrite(tmp, sizeof(char), 3 * bmp->width * bmp->height, fp) != 3 * bmp->width * bmp->height) {
		fprintf(stderr, "can't write image data\n");
		exit(1);
	}
	free(tmp);
	fclose(fp);
}
