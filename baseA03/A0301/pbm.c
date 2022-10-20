#include "includes.h"

/***************************************************/
/* Loading of PBM                                  */
/***************************************************/
Bitmap* loadPbm(char* name)
{
	FILE* fp;
	Bitmap* bmp;
	char buf[BUFF];
	unsigned char* tmp;
	int i, j, x, y, cnt, num;

	if ((fp = fopen(name, "rb")) == NULL) {
		fprintf(stderr, "can't open file (%s)\n", name);
		exit(1);
	}
	if (fgets(buf, BUFF, fp) == NULL) {
		fprintf(stderr, "wrong pgm header\n");
		exit(1);
	}
	if (strncmp(buf, "P4", 2)) {
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
	num = RAISE(x / 8.0);
	if ((tmp = (unsigned char*)malloc(num * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	if ((bmp = (Bitmap*)malloc(sizeof(Bitmap))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	bmp->format = PBM;
	bmp->width = x;
	bmp->height = y;
	bmp->rmap = NULL;
	bmp->gmap = NULL;
	bmp->bmap = NULL;
	if ((bmp->map = (unsigned char*)malloc(x * y * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	for (j = 0; j < y; j++) {
		if (fread(tmp, sizeof(char), num, fp) != num) {
			fprintf(stderr, "can't read image data\n");
			exit(1);
		}
		cnt = 0;
		for (i = 0; i < x; i++) {
			bmp->map[j * x + i] = (tmp[cnt / 8] >> (7 - cnt % 8)) & 0x01;
			cnt++;
		}
	}
	free(tmp);
	fclose(fp);

	return bmp;
}

/***************************************************/
/* Saving of PBM                                   */
/***************************************************/
void savePbm(char* name, Bitmap* bmp)
{
	FILE* fp;
	unsigned char* tmp;
	int i, j, cnt, num;

	if (bmp->format != PBM) {
		fprintf(stderr, "wrong format\n");
		exit(1);
	}
	if ((fp = fopen(name, "wb")) == NULL) {
		fprintf(stderr, "can't open file (%s)\n", name);
		exit(1);
	}
	fprintf(fp, "P4\n%d %d\n", bmp->width, bmp->height);
	num = RAISE(bmp->width / 8.0);
	if ((tmp = (unsigned char*)malloc(num * sizeof(char))) == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	for (j = 0; j < bmp->height; j++) {
		cnt = 0;
		for (i = 0; i < bmp->width; i++) {
			if (bmp->map[j * bmp->width + i] == 0) {
				tmp[cnt / 8] = tmp[cnt / 8] & ~(0x80 >> cnt % 8);
			}
			else {
				tmp[cnt / 8] = tmp[cnt / 8] | (0x80 >> cnt % 8);
			}
			cnt++;
		}
		if (fwrite(tmp, sizeof(char), num, fp) != num) {
			fprintf(stderr, "can't write image data\n");
			exit(1);
		}
	}

	free(tmp);
	fclose(fp);
}