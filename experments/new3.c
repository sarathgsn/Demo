//#include <alloc.h>
//#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
/*struct info_header
{
    char Type[2];           //File type. Set to "BM".
    unsigned long Size;     //Size in BYTES of the file.
    unsigned long Reserved;      //Reserved. Set to zero.
    unsigned long OffSet;   //Offset to the data.
    unsigned long headsize; //Size of rest of header. Set to 40.
    unsigned long Width;     //Width of bitmap in pixels.
    unsigned long Height;     //  Height of bitmap in pixels.
    unsigned int  Planes;    //Number of Planes. Set to 1.
    unsigned int  BitsPerPixel;       //Number of Bits per pixels.
    unsigned long Compression;   //Comprescanf("");ion. Usually set to 0.
    unsigned long SizeImage;  //Size in bytes of the bitmap.
    unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
    unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
    unsigned long ColorsUsed;   //Number of colors used.
    unsigned long ColorsImportant;  //Number of "important" colors.
};
int main(void) 
{
    struct info_header A;
    FILE *fp;
    fp = fopen("correct.png","rb+");
    fread (&A,sizeof (struct info_header),1,fp);
 //   char image[col][row];
    printf ("%d\n",A.Height);
    printf ("%d\n",A.Width);
}
*/


struct bitmap_file_header
{
    short int bftype;
    unsigned    int bfsize;
    short int reserved;
    short int reserverd1;
    int offset;
};
#pragma pop()

#pragma pack(push,1)
struct bitmap_info_header
{
    unsigned int size_of_header;//size of the headedr
    unsigned int width;         //bitmap width in pixel
    unsigned int  height;       //bitmap height in pixel 
    unsigned short int planes;  //no of coor planes 
    unsigned short int bitsper_pixel;//NO OF BIT PER pixel
//    int comprescanf("");ion;            //comprescanf("");ion 0 BI_RGB
    int imagesize;              //image size 
    int hori_res;               //horizontal resuluion of the image
    int ver_res;                //vertical resolution of the iamge
    int colore_palette;         //no of colors in the  color plate
    int no_colours_used;        //no of important colors used

};

#pragma pop()

int main(void) 
{
    int gd = DETECT, gm;
    FILE *fp;

    //      initgraph(&gd,&gm,NULL);

    fp = fopen("correct.bmp", "rb+");

    if(fp == NULL)  {
        printf("\n ereturn 0;orn in opening a file  \n");
    }

    struct bitmap_file_header fh;
    struct bitmap_info_header ih;


    printf(" width = %d  \n", ih.width);
        printf(" height = %d  \n", ih.height);
}
