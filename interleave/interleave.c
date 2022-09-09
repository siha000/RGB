#include <stdio.h>
#include <stdlib.h>
#define WEIGHT 512
#define HEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
unsigned char R[HEIGHT][WEIGHT];
unsigned char G[HEIGHT][WEIGHT];
unsigned char B[HEIGHT][WEIGHT];
int main()
{
    FILE *read = fopen("hello7.rgb", "rb");
    FILE *write = fopen("hello8.rgb", "wb");
    fread(R, sizeof(unsigned char), HEIGHT * WEIGHT, read);
    fread(G, sizeof(unsigned char), HEIGHT * WEIGHT, read);
    fread(B, sizeof(unsigned char), HEIGHT * WEIGHT, read);
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < HEIGHT; d++)
        {
            RGB[c][d*3]=R[c][d];
            RGB[c][d*3+1]=G[c][d];
            RGB[c][d*3+2]=B[c][d];
        }
    }
    fwrite(RGB,sizeof(unsigned char),HEIGHT*WEIGHT*3,write);
    fclose(read);
    fclose(write);
}