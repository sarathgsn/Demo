#include<stdio.h>
#include<stdlib.h>


int main()
{
    FILE *fp;
    FILE *fpnew;
    char buff;
    int i;

    fp=fopen("beautiful.bmp","r");         //open the image file named beautiful.bmp from this same directory
    fpnew=fopen("beautiful_copy.bmp","w+");    //  w+ will create the file beautiful_copy.bmp

    //in bmp file the first 54 bits will be a header file

    for(i=0;i<54;i++)
    {
    fseek(fp,i,SEEK_SET);
	fread(&buff,sizeof(char),1,fp);
    fseek(fpnew,i,SEEK_SET);
	fwrite(&buff,sizeof(char),1,fpnew);
    }
    fclose(fp);
    fclose(fpnew);
}





