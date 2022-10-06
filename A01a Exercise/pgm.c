#include "includes.h"

/***************************************************/
/* Loading of PGM                                  */
/***************************************************/
Bitmap* loadPgm(char* name)
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
		fprintf(stderr, "wrong pgm header\n");
		exit(1);
	}
	if (strncmp(buf, "P5", 2)) {
		fprintf(stderr, "wrong pgm header\n");
		exit(1);
	}
	do {
		if (fgets(buf, BUFF, fp) == NULL) {
			fprintf(stderr, "wrong pgm header\n");
			exit(1);
		}
	} while (buf[0] == 0x23);
	sscanf(buf, "%d %d", &x, &y);
	do {
		fgets(buf, 255, fp);
	} while (buf[0] == 0x23);
	if ((tmp = (unsigned char*)malloc(x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	if (fread(tmp, sizeof(char), x * y, fp) != x * y) {
		fprintf(stderr, "can't read image data\n");
		exit(1);
	}
	fclose(fp);

	if ((bmp = (Bitmap*)malloc(sizeof(Bitmap))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	bmp->format = PGM;
	bmp->width = x;
	bmp->height = y;
	bmp->rmap = NULL;
	bmp->gmap = NULL;
	bmp->bmap = NULL;
	if ((bmp->map = (unsigned char*)malloc(x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	cnt = 0;
	for (j = 0; j < y; j++) {
		for (i = 0; i < x; i++) {
			bmp->map[j * x + i] = tmp[cnt++];
		}
	}
	free(tmp);

	return bmp;
}

/***************************************************/
/* Saving of PGM                                   */
/***************************************************/
void savePgm(char* name, Bitmap* bmp)
{
	FILE* fp;
	unsigned char* tmp;

	if (bmp->format != PGM) {
		fprintf(stderr, "wrong format\n");
		exit(1);
	}
	if ((fp = fopen(name, "wb")) == NULL) {
		fprintf(stderr, "can't open file (%s)\n", name);
		exit(1);
	}
	fprintf(fp, "P5\n%d %d\n255\n", bmp->width, bmp->height);
	if ((tmp = (unsigned char*)malloc(bmp->width * bmp->height * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	if (fwrite(bmp->map, sizeof(char), bmp->width * bmp->height, fp) != bmp->width * bmp->height) {
		fprintf(stderr, "can't write image data\n");
		exit(1);
	}
	free(tmp);
	fclose(fp);
}
