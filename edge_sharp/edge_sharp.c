#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
char record[HEIGHT + 2][WEIGHT * 3 + 6] = {0};
unsigned char result[HEIGHT][WEIGHT * 3] = {0};

int main()
{
    FILE *read = fopen("TEXT.rgb", "rb");
    FILE *write = fopen("TEXT1.rgb", "wb");
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 1; c < HEIGHT; c++)
    {
        for (int d = 3; d < WEIGHT * 3; d++)
        {
            record[c][d] = RGB[c - 1][d - 3];
        }
    }

    for (int c = 1; c < HEIGHT; c++)
    {
        for (int d = 3; d < WEIGHT * 3; d += 3)
        {

            result[c - 1][d - 3] = ((9) * record[c][d] - record[c][d + 3] - record[c][d - 3] - record[c - 1][d] - record[c - 1][d + 3] - record[c - 1][d - 3] - record[c + 1][d] - record[c + 1][d + 3] - record[c + 1][d - 3]);
            result[c - 1][d - 2] = ((9) * record[c][d + 1] - record[c][d + 4] - record[c][d - 2] - record[c - 1][d + 1] - record[c - 1][d + 4] - record[c - 1][d - 2] - record[c + 1][d + 1] - record[c + 1][d + 4] - record[c + 1][d - 2]);
            result[c - 1][d - 1] = ((9) * record[c][d + 2] - record[c][d + 5] - record[c][d - 1] - record[c - 1][d + 2] - record[c - 1][d + 5] - record[c - 1][d - 1] - record[c + 1][d + 2] - record[c + 1][d + 5] - record[c + 1][d - 1]);
           /* RGB[c - 1][d - 3] += result[c - 1][d - 3];
            RGB[c - 1][d - 2] += result[c - 1][d - 2];
            RGB[c - 1][d - 1] += result[c - 1][d - 1];/*
            /* result[c - 1][d - 3] = 9 * record[c][d] - record[c - 1][d] - record[c + 1][d] - record[c][d - 3] - record[c][d + 3] - record[c - 1][d + 3] - record[c - 1][d - 3] - record[c + 1][d - 3] - record[c + 1][d + 3];
             result[c - 1][d - 2] = 9 * record[c][d + 1] - record[c - 1][d + 1] - record[c + 1][d + 1] - record[c][d - 2] - record[c][d + 4] - record[c - 1][d + 4] - record[c - 1][d - 2] - record[c + 1][d - 2] - record[c + 1][d + 4];
             result[c - 1][d - 1] = 9 * record[c][d + 2] - record[c - 1][d + 2] - record[c + 1][d + 2] - record[c][d - 1] - record[c][d + 5] - record[c - 1][d + 5] - record[c - 1][d - 1] - record[c + 1][d - 1] - record[c + 1][d + 5];
         */
        }
    }

    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    fclose(read);
    fclose(write);
    return 0;
}