#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"
#include "string.h"
#include "stdlib.h"
#define wordwidth 10
#define wordheight 22
#define wordsize 660
stbi_uc * truetype[128];
stbi_uc ttype[128][wordsize];
void copyimage(int x,int y,int width,stbi_uc* src,int dx,int dy,int dwidth,stbi_uc* dest)
{
    dest[dx*dwidth*3+dy*3]=src[x*width*3+y*3];
    dest[dx*dwidth*3+dy*3+1]=src[x*width*3+y*3+1];
    dest[dx*dwidth*3+dy*3+2]=src[x*width*3+y*3+2];
    //printf("%d %d %d\n",src[x*width*3+y*3],src[x*width*3+y*3+1],src[x*width*3+y*3+2]);
}
void outputimage(stbi_uc * imagedata,int width,int height,int srcx,int srcy,int num)
{
    char str[80];
    char tstr[50];
    str[0]='\0';
    itoa(num,tstr,10);
    strcat(str,"d:\\image\\");
    strcat(str,tstr);
    strcat(str,".bmp");
    stbi_uc * destimage = (stbi_uc*)malloc(wordsize);
    for (int i=0;i<wordheight;i++)
        for (int j=0;j<wordwidth;j++)
        {
            //printf("%d %d\n",srcx+i,srcy+j);
            copyimage(srcx+i,srcy+j,width,imagedata,i,j,wordwidth,destimage);
        }
    //printf("%s\n",str);
    stbi_write_bmp(str,wordwidth,wordheight,3,destimage);
    truetype[num]=destimage;
}

void readimage()
{
    int width;
    int height;
    int components;
    stbi_uc * imagedata = stbi_load("d:\\image\\heiti.bmp",&width,&height,&components,3);
    for (int i=' ';i<=126;i++)
        outputimage(imagedata,width,height,82,360+(i-' ')*wordwidth*2,i);
    //printf("%d %d %d\n",width,height,components);
    freopen("d:\\image\\outputlib.txt","w",stdout);
    printf("stbi_uc ttype[128][%d]={",wordsize);
    for (int i=0;i<128;i++)
    {
        printf("{");
        int pi=i;
        if (i<' ' || i==127) pi=' ';
        for (int j=0;j<wordsize;j++)
        {
            printf("%d",truetype[pi][j]);
            ttype[pi][j]=truetype[pi][j];
            if (j!=wordsize-1) printf(",");
        }
        printf("}");
        if (i!=127) printf(",");
    }
    printf("}");
}
#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640
#define WINDOW_SIZE 921600
stbi_uc command[WINDOW_SIZE];
int commandline=0;

int main(int argc, char *argv[])
{
    readimage();
    return 0;
}
