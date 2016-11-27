#include "font.h"
#include <thumips.h>
#include <stdio.h>
#define DEFAULT_COLOR 448
#define DEFAULT_COLOG 56
#define DEFAULT_COLOB 7
#define DEFAULT_COLOW 511
volatile int* memorie = (int*)0xBA000000;
volatile int* beginaddress = (int*)0xBA000000;
static int commandbeginaddress = 0;
static int command[ROW_NUM][COLUMN_NUM];
static int commandcolor[ROW_NUM][COLUMN_NUM];
static bool iscommand = 1;
static int cursorx=0,cursory=0;
static int commandpage=0;
void renderachar(int x, int y, int ch, int color)
{
    if (ch < ' ' || ch > 127) ch = ' ';
    const unsigned *nowposition =fontmap[ch - ' '];
    unsigned cursor = nowposition[0];
    int i, j, pos = 0,k=128;
    unsigned char* dest = memorie +x * WINDOW_WIDTH * CHAR_HEIGHT + y * CHAR_WIDTH + BEGIN_PIXEL;
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
                    *dest = 255;
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
    *(beginaddress)=0;
    commandbeginaddress=0;
    commandpage=0;
}
void vga_newline()
{
    if (commandpage)
    {
        commandbeginaddress += ONE_ROW_NUM;
        if (commandbeginaddress>WINDOW_SIZE) commandbeginaddress=0;
        *(beginaddress) = commandbeginaddress;
    }
    int i;
    for (i=0;i<COLUMN_NUM;i++)
    {
        command[cursorx][j]=0;
        commandcolor[cursorx][j]=0;
        renderachar(cursorx,i,0,DEFAULT_COLOW);
    }
}
void vga_putch(int thischar, int color)
{
    if (!iscommand) return;
    if (thischar=='\n' || thischar=='\r')
    {
        cursorx=cursorx+1;
        if (cursorx==ROW_NUM) cursorx=0,commandpage=1;
        vga_newline();
        cursory=0;

    }
    else if (thischar=='\b')
    {
	if (cursory!=0) cursory--;
	else
	{
	    cursorx--;
        if (cursorx<0) cursorx=ROW_NUM-1;
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
            {
                cursory=0;
                cursorx=cursorx+1;
                if (cursorx==ROW_NUM) cursorx=0,commandpage=1;
                vga_newline();
            }
        }
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
    iscommand=1;
    int i, j;
    for (i=0;i<ROW_NUM;i++)
        for (j=0;j<COLUMN_NUM;j++)
            renderachar(i,j,command[i][j],commandcolor[i][j]);
}

void changetoapp()
{
    iscommand=0;
    int i;
    for (i=0;i<WINDOW_SIZE;i++)
        memorie[i]=0;
}
