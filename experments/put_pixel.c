#include<graphics.h>
//#include<conio.h>

main()
{   int i = 0;
    int gd = DETECT, gm;
    int data = 20;
    int data1 = 50;
    initgraph(&gd, &gm, NULL);
while (i < 100) {
    putpixel(data, data1, RED);
    putpixel(data+100, data1+110, GREEN);
    putpixel(data+200, data1+210, WHITE);
    i++;
    data++;
    data1++;
}
    getchar();
    closegraph();
    return 0;
}
