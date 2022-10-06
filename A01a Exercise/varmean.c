#include "includes.h"


void find_mean(Bitmap* bmp, float * result){
    float total_arr = bmp->height * bmp->width, red_sum = 0, green_sum = 0, blue_sum = 0;
    for(int i = 0 ; i < total_arr;i++){
        red_sum = red_sum + bmp->rmap[i];
        green_sum = green_sum + bmp->gmap[i];
        blue_sum = blue_sum + bmp->bmap[i];
    }
    result[0] = red_sum / total_arr;
    result[1]= green_sum / total_arr;
    result[2] = blue_sum / total_arr;

}

void find_variance(Bitmap* bmp, float * result, float * mean_result){
    float total_arr = bmp->height * bmp->width, red_Vsum = 0, green_Vsum = 0, blue_Vsum = 0;
    for(int i = 0 ; i < total_arr;i++){
        red_Vsum = red_Vsum + pow((bmp->rmap[i]- mean_result[0]),2);
        green_Vsum = green_Vsum + pow((bmp->gmap[i]- mean_result[0]),2);
        blue_Vsum = blue_Vsum + pow((bmp->bmap[i]- mean_result[0]),2);
    }
    result[0] = red_Vsum / total_arr;
    result[1] = green_Vsum / total_arr;
    result[2] = blue_Vsum / total_arr;
}
