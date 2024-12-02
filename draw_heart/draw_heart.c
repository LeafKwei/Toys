#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

//#define DBG                 //Turn on if you adjusted 'SCALE', to get a new CANVAS_WIDTH, CANVAS_HEIGHT, OFFSET_X, and OFFSET_Y
#define PI 3.14
#define STEP 0.1
#define SCALE 2               //Scale of the heart
#define CANVAS_WIDTH 64
#define CANVAS_HEIGHT 58
#define OFFSET_X 32
#define OFFSET_Y 23
#define MARK ('*')
#define SPACE (' ')
#define DRAW_DELAY (100 * 1000)

int min_nega_x = 0;
int max_posi_x = 0;
int min_nega_y = 0;
int max_posi_y = 0;
char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

double y_equ(double t){
    return 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
}

double x_equ(double t){
    return 16 * pow(sin(t), 3);
}

int isNoContent(char *line, int len){
    for(int i = 0; i < len; i++){
        if(line[i]) return 0;
    }
    return 1;
}

int main(void){
    double t = 0;
    for(t; t <= (2 * PI); t += STEP){
        int x = floor(x_equ(t) * SCALE);
        int y = floor(y_equ(t) * SCALE);
        y = -y;                              //To avoid the heart to be inverted
        
        #ifdef DBG
        if(x < min_nega_x) min_nega_x = x;
        if(y < min_nega_y) min_nega_y = y;
        if(x > max_posi_x) max_posi_x = x;
        if(y > max_posi_y) max_posi_y = y;
        #endif
        
        x = x + OFFSET_X;
        y = y + OFFSET_Y;
        
        #ifndef DBG
        canvas[y][x] = 1;
        #endif
    }

    #ifdef DBG
    printf("canvas_width should be %d, canvas_height should be %d\n", abs(min_nega_x) + max_posi_x + 1, abs(min_nega_y) + max_posi_y + 1);
    printf("offset_x should be %d, offset_y should be %d\n", abs(min_nega_x), abs(min_nega_y));
    system("pause");
    #endif

    #ifndef DBG
    for(int y = 0; y < CANVAS_HEIGHT; y++){
        if(isNoContent(canvas[y], CANVAS_WIDTH)) continue;
        for(int x = 0; x < CANVAS_WIDTH; x++){
            if(canvas[y][x])
                printf("%c", MARK);
            else
                printf("%c", SPACE);
        }
        usleep(DRAW_DELAY);
        printf("\n");
    }
    #endif
}