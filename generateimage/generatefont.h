#ifndef GENERATEFONT_H
#define GENERATEFONT_H
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
void generatefont(string filename)
{
    FILE*f = fopen(filename.c_str(),"r");
    FILE*g = fopen("d:\\image\\fontm.txt","w");
    char s1[20000];
    unsigned int s;
    fprintf(g,"static const unsigned fontmap[95][3]={");
    for (int i=32;i<=126;i++)
    {

        for (int j=0;j<11;j++)
            fscanf(f,"%s",s1);
        int width,height,xoffset,yoffset;
        fscanf(f,"%d%d%d%d",&width,&height,&xoffset,&yoffset);
        yoffset=11-yoffset-height;
        cout<<dec<<i<<' '<<width<<' '<<yoffset<<endl;
        fscanf(f,"%s",s1);
        unsigned int temp[3];
        for (int j=0;j<3;j++) temp[j]=0;
        for (int j=0;j<height;j++)
        {
            s=0;
            char t;
            fscanf(f,"%c",&t);
            fscanf(f,"%c",&t);
            if (t>='0' && t<='9')
                s += (t-'0')*16;
            else
                s += (t-'A'+10)*16;
            fscanf(f,"%c",&t);
            if (t>='0' && t<='9')
                s += (t-'0');
            else
                s += (t-'A'+10);
            s=(s>>xoffset);

            unsigned int sj = j + yoffset;
            cout<<dec<<sj<<' '<<hex<<s<<' '<<(s << (sj%4*8))<<endl;
            temp[sj/4] += (s << (sj%4*8));
        }
        cout<<hex<<temp[0]<<' '<<temp[1]<<' '<<temp[2]<<endl<<endl;
        fprintf(g,"{0x%x,0x%x,0x%x}",temp[0],temp[1],temp[2]);
        if (i!=126) fprintf(g,",");
        fscanf(f,"%s",s1);
    }
    fprintf(g,"};");
    fclose(f);
    fclose(g);
}

#endif // GENERATEFONT_H
