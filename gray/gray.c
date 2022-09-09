#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3];
unsigned char record[HEIGHT][WEIGHT * 3] = {0};
int main()
{
    FILE *read = fopen("TEXT.rgb", "rb");
    FILE *write = fopen("TEXT1.rgb", "wb");
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d+=3)
        {
            char temp = (RGB[c][d] + RGB[c][d + 1] + RGB[c][d + 2]) / 3;
            record[c][d] = temp;
            record[c][d + 1] = temp;
            record[c][d + 2] = temp;
        }
    }
    fwrite(record, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    fclose(read);
    fclose(write);
}