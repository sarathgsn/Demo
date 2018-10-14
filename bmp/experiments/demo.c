#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#pragma pack(push,1)

struct file_header
{
    short int bftype;
    unsigned    int bfsize;
    short int reserved;
    short int reserverd1;
    int offset;
};
#pragma pop()


#pragma pack(push,1)
struct info_header
{
    unsigned   int size_of_header;
    unsigned   int width;
    unsigned  int  height;
    unsigned    short int planes;
    unsigned    short  int bitsper_pixel;
    int compression;
    int imagesize;
    int hori_res;
    int ver_res;
    int colore_palette;
    int no_colours_used;

};

#pragma pop()

 struct colour
{
  unsigned  char r;
  unsigned   char g;
  unsigned  char b;
//  unsigned char res;
};
struct a
{
    char a:1;
    char b:1;
    char c:1;
    char d:1;
    char e:1;
    char f:1;
    char g:1;
    char h:1;
};



int main(char *argc, char *argv[]) 
{
  int gd = DETECT, gm;
    FILE *fp;

   initgraph(&gd,&gm,NULL);

    fp = fopen(argv[1], "rb");

    if(fp == NULL)
    {
        printf("\n errorn in opening a file  \n");
    }
    struct file_header fh;
    struct info_header ih;
    int data;
    struct  colour sc;
    //   fsee 
    //   fwrite("hello haiiiiiiiiiiiiiiiiiiii", 10000, 1, fp);

/*    printf("\n sizeof fileheader = %lu   \n", sizeof(fh));

    printf("\n sizeof infoheader = %lu  \n", sizeof(ih));
*/
    //printf("\n sizeof struct colour = %d  \n", sizeof(sc));

   fread(&fh, sizeof(struct file_header), 1, fp);
  /*  printf("\n bftype = %d  \n", fh.bftype);
    printf("\n bfsize = %d  \n", fh.bfsize);
    printf("\n bftype = %d  \n", fh.bftype);
    printf("\n reserved 1 = %d  \n", fh.reserverd1);
    printf("\n offset = %d  \n", fh.offset);
*/
    fread(&ih, sizeof(struct info_header), 1, fp);
  /*  printf("\n sizeofheader = %d  \n", ih.size_of_header);

    printf("\n width = %d  \n", ih.width);
    printf("\n height = %d  \n", ih.height);

    printf("\n planes = %d  \n", ih.planes);
    printf("\n bitsper_pixel = %d  \n", ih.bitsper_pixel);
    printf("\n compression = %d  \n", ih.compression);
    printf("\n imagesize = %d  \n", ih.imagesize);
    printf("\n hori_res = %d  \n",ih.hori_res);
    printf("\n ver_res = %d  \n",ih.ver_res);
    printf("\n colore_palette = %d   \n", ih.colore_palette);
    printf("\n no_of_colours_used  = %d \n", ih.no_colours_used);
  */
    unsigned char br;
    int a,b;
    int j = 0;
    int i = ih.height;
    int c , in;
                                    
   
  fseek(fp, fh.offset , SEEK_SET);
  
   while ( i > 0 ) 
   {

       for ( j = 0 ; j < ih.width; j++) {
       fread(&sc, sizeof(struct colour), 1, fp);

       putpixel( j,i ,sc.b);
//       putpixel( j,i+1,sc.g);
 //      putpixel( j,i+2,sc.r);
       }
       i--;
       }
/*
   struct a ar;
   while ( i > 0 ) 
   {

       for ( j = 0 ; j < ih.width; j++) {
       fread(&ar, sizeof(unsigned char), 1, fp);

       putpixel( j,i ,ar.a);
       putpixel( j,i+1 ,ar.b);
       putpixel( j,i+2 ,ar.c);
       putpixel( j,i+3 ,ar.d);
       putpixel( j,i+4 ,ar.e);
       putpixel( j,i+5 ,ar.f);
       putpixel( j,i+6 ,ar.g);
       putpixel( j,i+7 ,ar.h);
      

    }
       i--;
   }
*/












   //    printf("\n %d  %d %d  \n", sc.b, sc.g, sc.r);
  


/*  fseek(fp, fh.offset , SEEK_SET);
  Datas=(unsigned char*) calloc(ih.width/2+1, sizeof(unsigned char)); 
  for(b=ih.height;b >= 0; b--)
  {
      fread(Datas, sizeof(unsigned char), ih.width/2    , fp);                   
       c=0;
       in=0;
      for(a=0; a < ih.width;a+=2)
      {
          c =  Datas[in];
          putpixel(a+i,b+j,c);
         c = Datas[in];
          putpixel(a+1+i,b+j,c);
          in++;
      }
  }
*/
/*
 while(i < 100) {

      
 for ( j = 0 ; j < 256; j++) {

    fread(&ar, 1,1, fp) ;
  //  printf("\n ar =  %d  \n", ar);
 // sleep(1);
//  ptr = (int *) &ar;
    putpixel(i,j, ar);
 }
i++;
 
}
//    closegraph();
  */ getchar(); 
    return 0;
}





