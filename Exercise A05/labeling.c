#include "includes.h"

static int label_lut[MAX_LABEL];
static int label_lut2[MAX_LABEL];

int labeling(Bitmap* binIM, Bitmap* lblIM)
{
	int x, y, i;
	int label_num = 1;
	int pack_label_num;

	for (y = 0; y < lblIM->height; y++)
		for (x = 0; x < lblIM->width; x++)
			lblIM->map[y * lblIM->width + x] = UNLABEL;

	for (i = 1; i < MAX_LABEL; i++)
		label_lut[i] = i;

	for (y = 0; y < lblIM->height; y++)
		for (x = 0; x < lblIM->width; x++)
			if (binIM->map[y * binIM->width + x] == OBJ)
				lblIM->map[y * lblIM->width + x] = min_neighbors_label(lblIM, y, x, &label_num);

	pack_label_num = pack_label(label_num);

	if (label_num > 0) {
		for (y = 0; y < lblIM->height; y++)
			for (x = 0; x < lblIM->width; x++)
				lblIM->map[y * lblIM->width + x] = label_lut2[lblIM->map[y * lblIM->width + x]];
		return pack_label_num;
	}
	else return 0;
}

int min_neighbors_label(Bitmap* lblIM, int y, int x, int* num)
{
	int min_label, label1, label2, label3, label4;

	label1 = label2 = label3 = label4 = UNLABEL; /* initialization */

	if ((y - 1 >= 0) && (x - 1 >= 0)) /* up-left */
		label1 = lblIM->map[(y - 1) * lblIM->width + (x - 1)];
	if (y - 1 >= 0) /* up */
		label2 = lblIM->map[(y - 1) * lblIM->width + x];
	if ((y - 1 >= 0) && (x + 1 < lblIM->width)) /* up-right */
		label3 = lblIM->map[(y - 1) * lblIM->width + (x + 1)];
	if (x - 1 >= 0) /* left */
		label4 = lblIM->map[y * lblIM->width + (x - 1)];

	min_label = MIN(MIN(MIN(label1, label2), label3), label4);

	if (min_label == UNLABEL) { /* new label */
		min_label = ++(*num);
	}
	else {
		/* renew LUT */
		lookup_table(label1, min_label, *num);
		lookup_table(label2, min_label, *num);
		lookup_table(label3, min_label, *num);
		lookup_table(label4, min_label, *num);
	}
	return min_label;
}

void lookup_table(int label, int min_label, int num)
{
	int i;
	int old_label, new_label;

	if (label == UNLABEL) return;
	if (label_lut[label] == min_label) return;

	new_label = MIN(label_lut[label], min_label);
	old_label = MAX(label_lut[label], min_label);

	for (i = 1; i <= num; i++)
		if (label_lut[i] == old_label) label_lut[i] = new_label;
}


int pack_label(int num)
{
	int i;
	int new_label_num = 0;

	for (i = 1; i <= num; i++) {
		if (label_lut[i] != i) {
			label_lut2[i] = label_lut2[label_lut[i]];
		}
		else label_lut2[i] = new_label_num++;
	}
	return new_label_num;
}

