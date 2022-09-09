#include<stdio.h>
#include<stdio.h>
#define HEIGHT 512
#define WEIGHT 512
unsigned char RGB[HEIGHT][WEIGHT*3]={0};

int main()
{
    FILE *read=fopen("color.rgb","rb");
    FILE *write=fopen("color3.rgb","wb");
    fread(RGB,sizeof(unsigned char),HEIGHT*WEIGHT*3,read);
    for(int c=0;c<HEIGHT;c++)
    {
        for(int d=0;d<WEIGHT*3;d++)
        {
            if(d%3!=2)
            {
                RGB[c][d]=0;
            }
        }
    }
    fwrite(RGB,sizeof(unsigned char),HEIGHT*WEIGHT*3,write);
    fclose(read);
    fclose(write);
    return 0;
}