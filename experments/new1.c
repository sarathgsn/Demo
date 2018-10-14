#include <graphics.h>
#include<stdio.h>
int main(void) 
{
    //PImage img;
    int  img;
    size(340,240);
    img = loadImage("correct.pmg");

    image(img,0,0);
    return 0;
}
