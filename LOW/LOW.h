#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char record[HEIGHT][WEIGHT * 3] = {0};
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
unsigned char dp[HEIGHT][WEIGHT] = {0};
unsigned char result[HEIGHT][WEIGHT * 3];
int main()
{
    FILE *read = fopen("TEXT.rgb", "rb");
    FILE *write = fopen("TEXT1.rgb", "wb");
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d += 3)
        {
            char temp = (RGB[c][d] + RGB[c][d + 1] + RGB[c][d + 2]) / 3;
            record[c][d] = temp;
            record[c][d + 1] = temp;
            record[c][d + 2] = temp;
        }
    }
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d += 3)
        {
            char temp = (record[c][d] + record[c][d + 3] + record[c][d + 6] + record[c + 1][d] + record[c + 1][d + 3] + record[c + 1][d + 6] + record[c + 2][d] + record[c + 2][d + 3] + record[c + 2][d + 6]) / 9;
            result[c][d] = temp;
            result[c][d + 1] = temp;
            result[c][d + 2] = temp;
        }
    }
    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}