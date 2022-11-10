#include "includes.h"

int detect_contour(Bitmap *labelIM, int label_number, Bitmap *edgeIM)
{
	int i, x, y, length;

	for (y = 0; y < edgeIM->height; y++)
		for (x = 0; x < edgeIM->width; x++)
			edgeIM->map[y * edgeIM->width + x] = 0;

	for (i = 1; i < label_number; i++) {
		length = calc_chain_code(labelIM, i, edgeIM);
		printf("chain code length = %d\n", length);
	}

	return 0;
}

int calc_chain_code(Bitmap* labelIM, int label_no, Bitmap* edgeIM)
{
        /*********************************************/
	int chain_code[8][2] = {
		{ 0, 1},
		{-1, 1},
		{-1, 0},
		{-1,-1},
		{ 0,-1},
		{ 1,-1},
		{ 1, 0},
		{ 1, 1} };
	int next_code_no[8] = { 7,7, 1, 1, 3, 3, 5, 5}; /* next start code */
        /*********************************************/

	int x, y, xx, yy, start_x, start_y;
	int code_no, found, code_length;
	char code_str[CODE_LENGTH_MAX];

	for (y = 0; y < labelIM->height; y++)
		for (x = 0; x < labelIM->width; x++)
			if (labelIM->map[y * labelIM->width + x] == label_no) goto LABEL_FOUND;

LABEL_FOUND:
	start_x = x;
	start_y = y;
	code_no = 5;
	code_length = 0;
	do {
		found = 0;
		do {
			xx = x + chain_code[code_no][1];
			yy = y + chain_code[code_no][0];
			if ((xx >= 0 && xx < labelIM->width && yy >= 0 && yy < labelIM->height) && labelIM->map[yy * labelIM->width + xx] == label_no)
				found = 1;
			else {
				code_no++;
				if (code_no > 7) code_no = 0;
			}
		} while (found == 0);
		sprintf(&code_str[code_length], "%d", code_no);
		code_length++;
		x = xx;
		y = yy;
		edgeIM->map[y * edgeIM->width + x] = 1;
		code_no = next_code_no[code_no];
	} while (!(x == start_x && y == start_y));
	printf("(%d,%d) %s\n", start_x, start_y, code_str);

	return code_length;
}
