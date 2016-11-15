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
stbi_uc ttype[128][wordsize/3];
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
    printf("stbi_uc ttype[128][%d]={",wordsize/3);
    for (int i=0;i<128;i++)
    {
        printf("{");
        int pi=i;
        if (i<' ' || i==127) pi=' ';
        for (int j=0;j<wordsize/3;j++)
        {
            unsigned char result=0;
            result += truetype[pi][j*3]*2;
            result += truetype[pi][j*3+1]/4;
            result += truetype[pi][j*3+2]/32;
            printf("%d",result);
            ttype[pi][j]=result;
            if (j!=wordsize/3-1) printf(",");
        }
        printf("}");
        if (i!=127) printf(",");
    }
    printf("}");
}
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define ROW_NUM 27
#define COLUMN_NUM 80
#define CHAR_WIDTH 10
#define CHAR_HEIGHT 22
#define WINDOW_SIZE 480000
#define COMMAND_SIZE 2160
unsigned char command[COMMAND_SIZE];
unsigned char commandcolor[COMMAND_SIZE];
unsigned char memorie[WINDOW_SIZE];
bool iscommand = true;
int commandline=0;
int cursorx=0,cursory=0;
void vga_init()
{
    iscommand = true;
    for (int i=0;i<WINDOW_SIZE;i++)
        memorie[i]=0;
    for (int i=0;i<COMMAND_SIZE;i++)
        command[i]=0,commandcolor[i]=0;
}
void rendercommand()
{
    for (int i=0;i<ROW_NUM;i++)
    {
        int rx=i*CHAR_HEIGHT;
        for (int j=0;j<COLUMN_NUM;j++)
        {
            int ry=j*CHAR_WIDTH;
            int commandwz=i*COLUMN_NUM+j;
            for (int ii=0;ii<CHAR_HEIGHT;ii++)
                for (int jj=0;jj<CHAR_WIDTH;jj++)
                {
                    int wz=ii*CHAR_WIDTH+jj;
                    if (commandcolor[commandwz])
                    {
                        if (ttype[command[commandwz]][wz])
                            memorie[(ii+rx)*WINDOW_WIDTH+(jj+ry)]=commandcolor[commandwz];
                        else
                            memorie[(ii+rx)*WINDOW_WIDTH+(jj+ry)]=0;
                    } else
                    {
                        memorie[(ii+rx)*WINDOW_WIDTH+(jj+ry)]=ttype[command[commandwz]][wz];
                    }
                }
            if (i==cursorx && j==cursory)
            {
                for (int ii=CHAR_HEIGHT-3;ii<CHAR_HEIGHT;ii++)
                    for (int jj=0;jj<CHAR_WIDTH;jj++)
                    {
                        memorie[(ii+rx)*WINDOW_WIDTH+(jj+ry)]=255;
                    }
            }
        }
    }
}

void vga_putchar(unsigned char thischar,unsigned char color)
{
    if (thischar=='\n' || thischar=='\r')
    {
        cursorx=cursorx+1;
        if (cursorx==ROW_NUM)
        {
            for (int i=0;i<COMMAND_SIZE-ROW_NUM;i++)
            {
                command[i]=command[i+ROW_NUM];
            }
            cursorx--;
        }
    }
    else
    {
        if (thischar>=' ' && thischar<127)
        {
            int cursor=cursorx*COLUMN_NUM+cursory;
            for (int i=COMMAND_SIZE-1;i>cursur;i--)
                command[i]=command[i-1];
            command[cursor]=thischar;
            color[cursor]=color;
        }
    }
    rendercommand();
}

int main(int argc, char *argv[])
{
    readimage();
    return 0;
}
