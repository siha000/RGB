#include <stdio.h>
#include <stdio.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT * 3];
char R[HEIGHT][WEIGHT];
char G[HEIGHT][WEIGHT];
char B[HEIGHT][WEIGHT];
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
            if (c + 2 < HEIGHT && d + 2 < WEIGHT)
            {
                char data_R[9] = {R[c][d],
                                  R[d][d + 1],
                                  R[c][d + 2],
                                  R[c + 1][d],
                                  R[c + 1][d + 1],
                                  R[c + 1][d + 2],
                                  R[c + 2][d],
                                  R[c + 2][d + 1],
                                  R[c + 2][d + 2]};

                char data_G[9] = {G[c][d],
                                  G[d][d + 1],
                                  G[c][d + 2],
                                  G[c + 1][d],
                                  G[c + 1][d + 1],
                                  G[c + 1][d + 2],
                                  G[c + 2][d],
                                  G[c + 2][d + 1],
                                  G[c + 2][d + 2]};

                char data_B[9] = {B[c][d],
                                  B[d][d + 1],
                                  B[c][d + 2],
                                  B[c + 1][d],
                                  B[c + 1][d + 1],
                                  B[c + 1][d + 2],
                                  B[c + 2][d],
                                  B[c + 2][d + 1],
                                  B[c + 2][d + 2]};

                char record_R, record_G, record_B;

                record_R = bubble_sort(data_R);
                record_G = bubble_sort(data_G);
                record_B = bubble_sort(data_B);

                result[c][d * 3] = record_R;
                result[c][d * 3 + 1] = record_G;
                result[c][d * 3 + 2] = record_B;
            }
        }
    }

    fwrite(result, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    return 0;
}