#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char R[HEIGHT][WEIGHT] = {0};
unsigned char G[HEIGHT][WEIGHT] = {0};
unsigned char B[HEIGHT][WEIGHT] = {0};
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
int main()
{
    FILE *read = fopen("hello1.rgb", "rb");
    FILE *write = fopen("hello7.rgb", "wb");
    // RGB 先R->G->B
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT*3, read);
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d++)
        {
            if (d % 3 == 0)
            {
                R[c][d/3] = RGB[c][d];
            }
            else if (d % 3 == 1)
            {
                G[c][d/3] = RGB[c][d];
            }
            else
            {
                B[c][d/3] = RGB[c][d];
            }
        }
    }
    fwrite(R, sizeof(unsigned char), HEIGHT * WEIGHT , write);
    fwrite(G, sizeof(unsigned char), HEIGHT * WEIGHT , write);
    fwrite(B, sizeof(unsigned char), HEIGHT * WEIGHT , write);
    fclose(read);
    fclose(write);
}