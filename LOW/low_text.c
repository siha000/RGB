#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
unsigned char R[HEIGHT][WEIGHT] = {0};
unsigned char G[HEIGHT][WEIGHT] = {0};
unsigned char B[HEIGHT][WEIGHT] = {0};
unsigned char result[HEIGHT][WEIGHT * 3];
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
    for (int f = 0; f < 30; f++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            for (int d = 0; d < WEIGHT; d++)
            {
                char temp_R = (R[c][d] + R[c][d + 1] + R[c][d + 2] + R[c + 1][d] + R[c + 1][d + 1] + R[c + 1][d + 2] + R[c + 2][d] + R[c + 2][d + 1] + R[c + 2][d + 2]) / 9;
                char temp_G = (G[c][d] + G[c][d + 1] + G[c][d + 2] + G[c + 1][d] + G[c + 1][d + 1] + G[c + 1][d + 2] + G[c + 2][d] + G[c + 2][d + 1] + G[c + 2][d + 2]) / 9;
                char temp_B = (B[c][d] + B[c][d + 1] + B[c][d + 2] + B[c + 1][d] + B[c + 1][d + 1] + B[c + 1][d + 2] + B[c + 2][d] + B[c + 2][d + 1] + B[c + 2][d + 2]) / 9;
                result[c][d * 3] = temp_R;
                result[c][d * 3 + 1] = temp_G;
                result[c][d * 3 + 2] = temp_B;
                R[c][d] = temp_R;
                G[c][d] = temp_G;
                B[c][d] = temp_B;
            }
        }
    }
    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}