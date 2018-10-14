

#include<graphics.h>
//#include<conio.h>
#include<stdio.h>

main()
{
    int gd = DETECT, gm, x = 100, y = 100, color;
    char arr[100];

    initgraph(&gd,&gm,"C:\\TC\\BGI");

    putpixel(x, y, GREEN);

    color = getpixel(x, y);

    sprintf(arr,"Color of pixel located at point(%d, %d) is %d",x,y,color);
    outtextxy(100,100,arr);

    getchar();
    closegraph();
    return 0;
}
