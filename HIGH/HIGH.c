#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3];
unsigned char R[HEIGHT][WEIGHT];
unsigned char G[HEIGHT][WEIGHT];
unsigned char B[HEIGHT][WEIGHT];
unsigned char record[HEIGHT][WEIGHT * 3];
int main()
{
    FILE *read = fopen("TEXT.rgb", "rb");
    FILE *write = fopen("TEXT1.rgb", "wb");
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT; d++)
        {
            R[c][d] = RGB[c][d * 3];
            G[c][d] = RGB[c][d * 3 + 1];
            B[c][d] = RGB[c][d * 3 + 2];
        }
    }
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 1; d < WEIGHT; d++)
        {
            record[c][d * 3] = abs(R[c][d - 1] - R[c][d + 1]);
            record[c][d * 3 + 1] = abs(G[c][d - 1] - G[c][d + 1]);
            record[c][d * 3 + 2] = abs(B[c][d - 1] - B[c][d + 1]);
        }
    }

    fwrite(record, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}