#include <stdio.h>
#include <stdio.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3];
char record[HEIGHT + 2][WEIGHT * 3 + 6] = {0};
unsigned char result[HEIGHT][WEIGHT * 3];
char bubble_sort(char *data)
{
    for (int c = 0; c < 9; c++)
    {
        for (int d = c; d < 9; d++)
        {
            if (data[c] > data[d])
            {
                int temp = data[c];
                data[c] = data[d];
                data[d] = temp;
            }
        }
    }
    return data[9 / 2];
}

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
    for (int c = 0; c < HEIGHT; c++)
    {
        for (int d = 0; d < WEIGHT * 3; d += 3)
        {
            char data_R[9] = {record[c][d],
                              record[c][d + 3],
                              record[c][d - 3],
                              record[c - 1][d],
                              record[c - 1][d + 3],
                              record[c - 1][d - 3],
                              record[c + 1][d],
                              record[c + 1][d + 3],
                              record[c + 1][d - 3]};

            char data_G[9] = {record[c][d + 1],
                              record[c][d + 4],
                              record[c][d - 2],
                              record[c - 1][d + 1],
                              record[c - 1][d + 4],
                              record[c - 1][d - 2],
                              record[c + 1][d + 1],
                              record[c + 1][d + 4],
                              record[c + 1][d - 2]};

            char data_B[9] = {record[c][d + 2],
                              record[c][d + 5],
                              record[c][d - 1],
                              record[c - 1][d + 2],
                              record[c - 1][d + 5],
                              record[c - 1][d - 1],
                              record[c + 1][d + 2],
                              record[c + 1][d + 5],
                              record[c + 1][d - 1]};

            char record_R, record_G, record_B;

            record_R = bubble_sort(data_R);
            record_G = bubble_sort(data_G);
            record_B = bubble_sort(data_B);

            result[c - 1][d - 3] = record_R;
            result[c - 1][d - 2] = record_G;
            result[c - 1][d - 1] = record_B;
        }
    }

    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}