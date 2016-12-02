#ifndef GENERATEBOX_H
#define GENERATEBOX_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <stb_image.h>
#include <stb_image_resize.h>
#include <stb_image_write.h>
using namespace std;
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
class color
{
public:
    unsigned int r,g,b;
};

color getcolor(int x,int y,unsigned char* thisimage,int width)
{
    color nowcolor;
    nowcolor.r=thisimage[x*width*3+y*3];
    nowcolor.g=thisimage[x*width*3+y*3+1];
    nowcolor.b=thisimage[x*width*3+y*3+2];
    return nowcolor;
}
void generatebox(string filename)
{
    int x,y,comp;
    unsigned char* image = stbi_load(filename.c_str(),&x,&y,&comp,3);
    cout<<x<<' '<<y<<endl;
    FILE* g = fopen("d:\\image\\test.txt","w");
    fprintf(g,"static const int test[%d][%d] = { ",y,x);
    for (int i=0;i<y;i++)
    {
        fprintf(g,"{");
        for (int j=0;j<x;j++)
        {
            color temp = getcolor(i,j,image,x);
            unsigned int thiscolor = 0;
            thiscolor += (((temp.r) / (255/7)) << 6);
            thiscolor += (((temp.g) / (255/7)) << 3);
            thiscolor += (((temp.b) / (255/7)));

            cout<<thiscolor<<endl;

            fprintf(g,"0x%x",thiscolor);
            if (j!=x-1) fprintf(g,",");
        }
        fprintf(g,"}");
        if (i!=y-1) fprintf(g,",");
    }
    fprintf(g,"};");
    fprintf(g,"\n");
    fclose(g);
}

#endif // GENERATEBOX_H
