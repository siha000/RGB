#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEIGHT 316
#define WEIGHT 316
unsigned char RGB[HEIGHT][WEIGHT * 3];
unsigned char record[160][160 * 3];
#pragma pack(1)

typedef struct BITMAP_header
{
   char name[2];
   unsigned int size;
   int garbage;
   unsigned int image_offset;
} header;

typedef struct DIB_HEADER
{
   unsigned int header_size;
   unsigned int width;
   unsigned int height;
   unsigned short int colorplanes;
   unsigned short int bitsperpixel;
   unsigned int compression;
   unsigned int image_size;
   unsigned int biXPelsPerMeter;
   unsigned int biYPelsPerMeter;
   unsigned int biClrUsed;
   unsigned int biClrImportant;
} DIBHEADER;

int main()
{
   FILE *read = fopen("Lenna.bmp", "rb");
   FILE *write = fopen("Lenna1.bmp", "wb");
   header header;
   DIBHEADER dibheader;
   fread(&header, sizeof(header), 1, read);
   fread(&dibheader, sizeof(dibheader), 1, read);
   fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
   for (int c = 0; c < HEIGHT; c += 2)
   {
      for (int d = 0; d < WEIGHT * 3; d += 6)
      {
         int temp_top_r = (RGB[c][d] + RGB[c][d + 3]) / 2;
         int temp_top_g = (RGB[c][d + 1] + RGB[c][d + 4]) / 2;
         int temp_top_b = (RGB[c][d + 2] + RGB[c][d + 5]) / 2;
         int temp_down_r = (RGB[c + 1][d] + RGB[c + 1][d + 3]) / 2;
         int temp_down_g = (RGB[c + 1][d + 1] + RGB[c + 1][d + 4]) / 2;
         int temp_down_b = (RGB[c + 1][d + 2] + RGB[c + 1][d + 5]) / 2;
         record[c / 2][d / 2] = (temp_top_r + temp_down_r) / 2;
         record[c / 2][d / 2 + 1] = (temp_top_g + temp_down_g) / 2;
         record[c / 2][d / 2 + 2] = (temp_top_b + temp_down_b) / 2;
      }
   }
   header.size = 160 * 160 * 3 ;
   dibheader.height = 160;
   dibheader.width = 160;
      fwrite(&header, sizeof(header), 1, write);
   fwrite(&dibheader, sizeof(dibheader), 1, write);
   fwrite(record, sizeof(unsigned char), 160 * 160  * 3, write);
   printf("%d %d \n", dibheader.height, dibheader.width);
   fclose(read);
   fclose(write);
}