#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3] = {0};
unsigned char record[HEIGHT + 2][WEIGHT * 3 + 6] = {0};
unsigned char result[HEIGHT][WEIGHT * 3];
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
            char record_Rx = (record[c][d] * 0 + record[c][d + 3] * 2 + record[c][d - 3] * (-2) + record[c - 1][d] * 0 + record[c - 1][d + 3] * 1 + record[c - 1][d - 3] * (-1) + record[c + 1][d] * 0 + record[c + 1][d + 3] * 1 + record[c + 1][d - 3] * (-1));
            char record_Gx = (record[c][d + 1] * 0 + record[c][d + 4] * 2 + record[c][d - 2] * (-2) + record[c - 1][d + 1] * 0 + record[c - 1][d + 4] * 1 + record[c - 1][d - 2] * (-1) + record[c + 1][d + 1] * 0 + record[c + 1][d + 4] * 1 + record[c + 1][d - 2] * (-1));
            char record_Bx = (record[c][d + 2] * 0 + record[c][d + 5] * 2 + record[c][d - 1] * (-2) + record[c - 1][d + 2] * 0 + record[c - 1][d + 5] * 1 + record[c - 1][d - 1] * (-1) + record[c + 1][d + 2] * 0 + record[c + 1][d + 5] * 1 + record[c + 1][d - 1] * (-1));
            char record_Ry = (record[c][d] * 0 + record[c][d + 3] * 0 + record[c][d - 3] * 0 + record[c - 1][d] * (-2) + record[c - 1][d + 3] * (-1) + record[c - 1][d - 3] * (-1) + record[c + 1][d] * 2 + record[c + 1][d + 3] * 1 + record[c + 1][d - 3] * 1);
            char record_Gy = (record[c][d + 1] * 0 + record[c][d + 4] * 0 + record[c][d - 2] * 0 + record[c - 1][d + 1] * (-2) + record[c - 1][d + 4] * (-1) + record[c - 1][d - 2] * (-1) + record[c + 1][d + 1] * 2 + record[c + 1][d + 4] * 1 + record[c + 1][d - 2] * 1);
            char record_By = (record[c][d + 2] * 0 + record[c][d + 5] * 0 + record[c][d - 1] * 0 + record[c - 1][d + 2] * (-2) + record[c - 1][d + 5] * (-1) + record[c - 1][d - 1] * (-1) + record[c + 1][d + 2] * 2 + record[c + 1][d + 5] * 1 + record[c + 1][d - 1] * 1);

            record_Rx = abs(record_Rx) + abs(record_Ry);
            record_Gx = abs(record_Gx) + abs(record_Gy);
            record_Bx = abs(record_Bx) + abs(record_By);

            result[c - 1][d - 3] = record_Rx > 255 ? 255 : record_Rx;
            result[c - 1][d - 2] = record_Gx > 255 ? 255 : record_Gx;
            result[c - 1][d - 1] = record_Bx > 255 ? 255 : record_Bx;
        }
    }
    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    fclose(read);
    fclose(write);
    return 0;
}