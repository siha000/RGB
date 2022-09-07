#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3];
unsigned char result[HEIGHT][WEIGHT * 3];
unsigned char record[HEIGHT + 2][WEIGHT * 3 + 6];
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
            char record_R = (record[c][d] * (-8) + record[c][d + 3] + record[c][d - 3] + record[c - 1][d] + record[c - 1][d + 3] + record[c - 1][d - 3] + record[c + 1][d] + record[c + 1][d + 3] + record[c + 1][d - 3]) ;
            char record_G = (record[c][d + 1] * (-8) + record[c][d + 4] + record[c][d - 2] + record[c - 1][d + 1] + record[c - 1][d + 4] + record[c - 1][d - 2] + record[c + 1][d + 1] + record[c + 1][d + 4] + record[c + 1][d - 2]) ;
            char record_B = (record[c][d + 2] * (-8) + record[c][d + 5] + record[c][d - 1] + record[c - 1][d + 2] + record[c - 1][d + 5] + record[c - 1][d - 1] + record[c + 1][d + 2] + record[c + 1][d + 5] + record[c + 1][d - 1]) ;
            result[c - 1][d - 3] = record_R < 0 ? 0 : record_R;
            result[c - 1][d - 2] = record_G < 0 ? 0 : record_G;
            result[c - 1][d - 1] = record_B < 0 ? 0 : record_B;
        }
    }

    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}