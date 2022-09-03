#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char record[HEIGHT][WEIGHT] = {0};
unsigned char R[HEIGHT][WEIGHT] = {0};
unsigned char G[HEIGHT][WEIGHT] = {0};
unsigned char B[HEIGHT][WEIGHT] = {0};
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
unsigned char DP_R[HEIGHT][WEIGHT] = {0};
unsigned char DP_G[HEIGHT][WEIGHT] = {0};
unsigned char DP_B[HEIGHT][WEIGHT] = {0};
unsigned char result[HEIGHT][WEIGHT * 3] = {0};
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
        for (int d = 0; d < WEIGHT; d++)
        {
            /*if (c + 2 < HEIGHT)
            {
                DP_R[c][d] = R[c][d] + R[c + 1][d] + R[c + 2][d];
                DP_G[c][d] = G[c][d] + G[c + 1][d] + G[c + 2][d];
                DP_B[c][d] = B[c][d] + B[c + 1][d] + B[c + 2][d];
            }
            else
            {
                if (c + 1 == HEIGHT)
                {
                    DP_R[c][d] = R[c][d];
                    DP_G[c][d] = G[c][d];
                    DP_B[c][d] = B[c][d];
                }
                else
                {
                    DP_R[c][d] = R[c][d] + R[c + 1][d];
                    DP_G[c][d] = G[c][d] + G[c + 1][d];
                    DP_B[c][d] = B[c][d] + B[c + 1][d];
                }
            }
            */
            DP_R[c][d] = R[c][d] + R[c + 1][d] + R[c + 2][d];
            DP_G[c][d] = G[c][d] + G[c + 1][d] + G[c + 2][d];
            DP_B[c][d] = B[c][d] + B[c + 1][d] + B[c + 2][d];
        }
    }
    for (int f = 0; f < 10; f++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            for (int d = 0; d < WEIGHT; d++)
            {
                char record_R, record_G, record_B;
                /*if (d + 2 < WEIGHT)
                {
                    record_R = (DP_R[c][d] + DP_R[c][d + 1] + DP_R[c][d + 2]) / 9;
                    record_G = (DP_G[c][d] + DP_G[c][d + 1] + DP_G[c][d + 2]) / 9;
                    record_B = (DP_B[c][d] + DP_B[c][d + 1] + DP_B[c][d + 2]) / 9;
                }
                else
                {
                    if (d + 1 == WEIGHT)
                    {
                        record_R = DP_R[c][d] / 9;
                        record_G = DP_G[c][d] / 9;
                        record_B = DP_B[c][d] / 9;
                    }
                    else
                    {
                        record_R = (DP_R[c][d] + DP_R[c][d + 1]) / 9;
                        record_G = (DP_G[c][d] + DP_G[c][d + 1]) / 9;
                        record_B = (DP_B[c][d] + DP_B[c][d + 1]) / 9;
                    }
                }
                */
                record_R = (R[c][d] + R[c][d + 1] + R[c][d + 2]) / 3;
                record_G = (G[c][d] + G[c][d + 1] + G[c][d + 2]) / 3;
                record_B = (B[c][d] + B[c][d + 1] + B[c][d + 2]) / 3;
                result[c][d * 3] = record_R;
                result[c][d * 3 + 1] = record_G;
                result[c][d * 3 + 2] = record_B;
            }
        }
    }
    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}