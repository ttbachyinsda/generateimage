#include <stdio.h>
#include <iostream>
#include <QDebug>
using namespace std;
static const unsigned fontmap[95][3]={{0x0,0x0,0x0},{0x10101000,0x101010,0x101000},{0x50282800,0x0,0x0},{0x7c282800,0x28282828,0x28287c28},{0x54381000,0x14183054,0x10385454},{0x58542400,0x28101028,0x485434},{0x50502000,0x54542020,0x344848},{0x20103000,0x0,0x0},{0x10100800,0x20202020,0x8101020},{0x10102000,0x8080808,0x20101008},{0x10000000,0x54385454,0x1054},{0x10000000,0x107c1010,0x1010},{0x0,0x0,0x20103000},{0x0,0x780000,0x0},{0x0,0x0,0x303000},{0x8040400,0x10101008,0x40402020},{0x48300000,0x48484848,0x304848},{0x30100000,0x10101010,0x101010},{0x48300000,0x20100848,0x784020},{0x48300000,0x8300848,0x304848},{0x18080000,0x48282818,0x8087c},{0x40780000,0x8487040,0x304848},{0x48300000,0x48704048,0x304848},{0x8780000,0x10101008,0x202020},{0x48300000,0x48304848,0x304848},{0x48300000,0x8384848,0x304848},{0x0,0x3030,0x303000},{0x0,0x3030,0x20103000},{0x8040000,0x20402010,0x40810},{0x0,0x78000078,0x0},{0x20400000,0x8040810,0x402010},{0x48300000,0x10100848,0x101000},{0x44380000,0x74545474,0x384448},{0x10100000,0x44282828,0x44447c},{0x44780000,0x44784444,0x784444},{0x44380000,0x40404044,0x384444},{0x48700000,0x44444444,0x704844},{0x407c0000,0x40784040,0x7c4040},{0x407c0000,0x40784040,0x404040},{0x44380000,0x4c404044,0x344c44},{0x44440000,0x447c4444,0x444444},{0x10380000,0x10101010,0x381010},{0x8080000,0x8080808,0x304848},{0x48480000,0x50605050,0x484850},{0x40400000,0x40404040,0x7c4040},{0x44440000,0x546c6c6c,0x545454},{0x64440000,0x54545464,0x444c4c},{0x44380000,0x44444444,0x384444},{0x44780000,0x40784444,0x404040},{0x44380000,0x44444444,0x344854},{0x44780000,0x48784444,0x444444},{0x44380000,0x8102044,0x384444},{0x107c0000,0x10101010,0x101010},{0x44440000,0x44444444,0x384444},{0x44440000,0x28282844,0x101010},{0x54540000,0x28545454,0x282828},{0x44440000,0x28102828,0x444428},{0x44440000,0x10102828,0x101010},{0x47c0000,0x20100808,0x7c4020},{0x10101c00,0x10101010,0x1c101010},{0x20404000,0x10101020,0x4040808},{0x10107000,0x10101010,0x70101010},{0x281000,0x0,0x0},{0x0,0x0,0xfc000000},{0x102000,0x0,0x0},{0x0,0x38483000,0x344848},{0x40400000,0x44447840,0x784444},{0x0,0x40443800,0x384440},{0x4040000,0x44443c04,0x3c4444},{0x0,0x7c443800,0x384440},{0x20180000,0x20207020,0x202020},{0x0,0x30483400,0x38443840},{0x40400000,0x44447840,0x444444},{0x10100000,0x10101000,0x101010},{0x10100000,0x10101000,0x60101010},{0x40400000,0x50484440,0x444870},{0x10100000,0x10101010,0x101010},{0x0,0x54546800,0x545454},{0x0,0x44447800,0x444444},{0x0,0x44443800,0x384444},{0x0,0x44447800,0x40407844},{0x0,0x44443c00,0x4043c44},{0x0,0x20302c00,0x202020},{0x0,0x30443800,0x384408},{0x20200000,0x20207020,0x182020},{0x0,0x44444400,0x3c4444},{0x0,0x28444400,0x101028},{0x0,0x54545400,0x282828},{0x0,0x10284400,0x442810},{0x0,0x28444400,0x60101028},{0x0,0x8047c00,0x7c2010},{0x10101800,0x10201010,0x18101010},{0x10101010,0x10101010,0x10101010},{0x10103000,0x10081010,0x30101010},{0x483400,0x0,0x0}};
#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 512
#define ROW_NUM 25
#define COLUMN_NUM 66
#define ONE_ROW_NUM 6144
#define CHAR_WIDTH 6
#define CHAR_HEIGHT 12
#define WINDOW_SIZE 153600
#define COMMAND_SIZE 1650
#define WINDOW_LEFT 9
#define BEGIN_PIXEL 2
#define DEFAULT_COLOR 448
#define DEFAULT_COLOG 56
#define DEFAULT_COLOB 7
#define DEFAULT_COLOW 511
static int command[25][66];
static int commandcolor[25][66];
static int memorie[WINDOW_SIZE];
static bool iscommand = false;
static int cursorx=0,cursory=0;
void renderachar(int x, int y, int ch, int color)
{
    if (ch < ' ' || ch > 127) ch = ' ';
    const unsigned *nowposition =fontmap[ch - ' '];
    unsigned cursor = nowposition[0];
    int i, j, pos = 0,k=128;
    int* dest = memorie +x * WINDOW_WIDTH * CHAR_HEIGHT + y * CHAR_WIDTH + BEGIN_PIXEL;
        for (i = 0; i < CHAR_HEIGHT; i ++)
        {
            for (j = 0; j < CHAR_WIDTH; j ++)
            {
                if (pos == 32)
                {
                    pos = 0;
                    cursor = *(++nowposition);
                }
                if (cursor & k)
                    *dest = color;
                else
                    *dest = 0;
                dest ++;
                k >>= 1;
            }
            pos += 8;
            cursor >>= 8;
            k=128;
            dest += WINDOW_WIDTH - CHAR_WIDTH;
        }
    command[x][y]=ch;
    commandcolor[x][y]=color;
}

void vga_init()
{
    iscommand = 1;
    int i, j;
    for (i=0;i<WINDOW_SIZE;i++)
        memorie[i]=0;
    for (i=0;i<ROW_NUM;i++)
        for (j=0;j<COLUMN_NUM;j++)
            command[i][j]=0,commandcolor[i][j]=0;
    cursorx=0,cursory=0;
}
void vga_passpage()
{
    cursorx=cursorx-10;
        int i, j;
        for (i=0;i<ROW_NUM-10;i++)
            for (j=0;j<COLUMN_NUM;j++)
                command[i][j]=command[i+10][j],commandcolor[i][j]=commandcolor[i+10][j];
        for (i=1;i<=10;i++)
            for (j=0;j<COLUMN_NUM;j++)
                command[ROW_NUM-i][j]=0;
    for (i=0;i<ROW_NUM;i++)
        for (j=0;j<COLUMN_NUM;j++)
                renderachar(i,j,command[i][j],commandcolor[i][j]);
}
void vga_putch(int thischar, int color)
{
    if (!iscommand) return;
    if (thischar=='\n' || thischar=='\r')
    {
        cursorx=cursorx+1;
        cursory=0;

    }
    else if (thischar=='\b')
    {
    if (cursory!=0) cursory--;
    else
    {
        cursorx--;
        cursory=COLUMN_NUM-1;
    }
    renderachar(cursorx,cursory,0,color);
    }
    else
    {
        if (thischar>=' ' && thischar<127)
        {
            renderachar(cursorx,cursory,thischar,color);
            cursory ++;
            if (cursory == COLUMN_NUM)
                cursory=0,cursorx++;

        }
    }
    if (cursorx==ROW_NUM)
    {
        vga_passpage();
    }
}
void vga_putchar(int thischar)
{
    if (thischar<='9' && thischar>='0')
        vga_putch(thischar,DEFAULT_COLOB);
    else
    vga_putch(thischar,DEFAULT_COLOW);
}

void changetoconsole()
{
    iscommand=true;
    for (int i=0;i<ROW_NUM;i++)
        for (int j=0;j<COLUMN_NUM;j++)
            renderachar(i,j,command[i][j],commandcolor[i][j]);
}

void changetoapp()
{
    iscommand=false;
    for (int i=0;i<WINDOW_SIZE;i++)
        memorie[i]=0;
}
