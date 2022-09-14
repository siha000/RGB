#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 512
#define WEIGHT 512
/*unsigned char RGB[HEIGHT][WEIGHT * 3];
unsigned char record[HEIGHT][WEIGHT * 3] = {0};
*/
int main()
{
    FILE *read = fopen("TEXT.rgb", "rb");
    FILE *write = fopen("TEXT1.rgb", "wb");
    unsigned char *RGB = (unsigned char *)malloc(sizeof(unsigned char) * HEIGHT * WEIGHT * 3);
    unsigned char *record = (unsigned char *)malloc(sizeof(unsigned char) * HEIGHT * WEIGHT * 3);

    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 0; c < HEIGHT * WEIGHT * 3; c += 3)
    {

        char temp = (RGB[c] + RGB[c + 1] + RGB[c + 2]) / 3;
        record[c] = temp;
        record[c + 1] = temp;
        record[c + 2] = temp;
    }
    fwrite(record, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    fclose(read);
    fclose(write);
    free(RGB);
    free(record);
}