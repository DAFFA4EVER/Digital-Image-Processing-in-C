/* labeling.h */

#define UNLABEL   255
#define MAX_LABEL 256
#define OBJ         1
#define BG          0

#define MAX(x,y) (((x)>(y))?(x):(y))
#define MIN(x,y) (((x)<(y))?(x):(y))

int labeling(Bitmap*, Bitmap*);
int min_neighbors_label(Bitmap*, int, int, int*);
int pack_label(int);
void lookup_table(int, int, int);