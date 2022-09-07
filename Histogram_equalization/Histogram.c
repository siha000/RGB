#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
double R[256] = {0}, G[256] = {0}, B[256] = {0};
double record_R[256] = {0}, record_G[256] = {0}, record_B[256] = {0};
double current_R, back_R = 0, current_G, back_G = 0, current_B, back_B = 0;
unsigned char result[HEIGHT][WEIGHT * 3] = {0};
int main()
{
    FILE *read = fopen("TEXT.rgb", "rb");
    FILE *write = fopen("TEXT1.rgb", "wb");
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d += 3)
        {
            record_R[RGB[c][d]] += 1;
            record_G[RGB[c][d + 1]] += 1;
            record_B[RGB[c][d + 2]] += 1;
        }
    }

    for (int c = 0; c < 256; c++)
    {
        current_R = record_R[c] / HEIGHT / WEIGHT;
        current_G = record_G[c] / HEIGHT / WEIGHT;
        current_B = record_B[c] / HEIGHT / WEIGHT;

        R[c] = current_R + back_R;
        G[c] = current_G + back_G;
        B[c] = current_B + back_B;

        back_R += current_R;
        back_G += current_G;
        back_B += current_B;

        record_R[c] = (R[c] - R[0]) * 255 / (1 - R[0]);
        record_G[c] = (G[c] - G[0]) * 255 / (1 - G[0]);
        record_B[c] = (B[c] - B[0]) * 255 / (1 - B[0]);
    }

    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d += 3)
        {
            result[c][d] = record_R[RGB[c][d]];
            result[c][d + 1] = record_G[RGB[c][d + 1]];
            result[c][d + 2] = record_B[RGB[c][d + 2]];
        }
    }
    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    fclose(read);
    fclose(write);
}