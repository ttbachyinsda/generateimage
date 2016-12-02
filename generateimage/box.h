#ifndef BOX_H
#define BOX_H
#include "boxdef.h"

struct counter
{
    int q[4];
    void clear()
    {
        int i;
        for (i=0;i<4;i++)
            q[i]=0;
    }
    void add()
    {
        q[3] ++;
        if (q[3]==10)
        {
            q[3]=0;
            q[2]++;
            if (q[2]==10)
            {
                q[2]=0;
                q[1]++;
                if (q[1]==10)
                {
                    q[1]=0;
                    q[0]++;
                    if (q[0]==10)
                        q[0]=0;
                }
            }
        }
    }
    void set(int num)
    {
        clear();
        while (num)
        {
            num--;
            add();
        }
    }
};

static int* boxmemorie = 0;
static int	boxgetposition[16] = { 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0 };
static int	boxmap[BOARD_HEIGHT][BOARD_WIDTH];
static int	boxrequiredtowin	= 0;
static int		boxmanx		= 0, boxmany = 0;
static int  boxnowlevel = 0;
static int	boxhaswin		= 0;

static counter boxmovements;

void boxrenderlevel()
{
    counter temp;
    temp.set(boxnowlevel);
    int color;
    if (boxnowlevel>=0 && boxnowlevel<33) color=DEFAULT_COLOW;
    if (boxnowlevel>=33 && boxnowlevel<66) color=DEFAULT_COLOG;
    if (boxnowlevel>=66 && boxnowlevel<100) color=DEFAULT_COLOR;

    int i,j,k;
    int nowhpixel=NUM1_HPIXEL;
    int nowwpixel=NUM1_WPIXEL;
    int nownum;
    int *dest;
    for (i=2;i<=3;i++)
    {
        nownum = temp.q[i];
        dest = boxmemorie + nowhpixel * WINDOW_WIDTH + nowwpixel;
        for (j=0;j<NUM_HEIGHT;j++)
        {
            for (k=0;k<NUM_WIDTH;k++)
            {
                (*dest) = boxnumimage[nownum][j][k]?color:0;
                dest ++;
            }
            dest += WINDOW_WIDTH - NUM_WIDTH;
        }

        nowwpixel += NUM_WIDTH;
    }
    dest = boxmemorie + LEVEL_HPIXEL * WINDOW_WIDTH + LEVEL_WPIXEL;
    for (j=0;j<TEXT_HEIGHT;j++)
    {
        for (k=0;k<TEXT_WIDTH;k++)
        {
            (*dest) = boxlevelimage[j][k]?color:0;
            dest ++;
        }
        dest += WINDOW_WIDTH - TEXT_WIDTH;
    }
}

void boxrendermovement()
{
    int color;
    if (boxnowlevel>=0 && boxnowlevel<33) color=DEFAULT_COLOW;
    if (boxnowlevel>=33 && boxnowlevel<66) color=DEFAULT_COLOG;
    if (boxnowlevel>=66 && boxnowlevel<100) color=DEFAULT_COLOR;

    int i,j,k;
    int nowhpixel=BS1_HPIXEL;
    int nowwpixel=BS1_WPIXEL+8;
    int nownum;
    int *dest;
    for (i=0;i<=3;i++)
    {
        nownum = boxmovements.q[i];
        dest = boxmemorie + nowhpixel * WINDOW_WIDTH + nowwpixel;
        for (j=0;j<NUM_HEIGHT;j++)
        {
            for (k=2;k<NUM_WIDTH-2;k++)
            {
                (*dest) = boxnumimage[nownum][j][k]?color:0;
                dest ++;
            }
            dest += WINDOW_WIDTH - NUM_WIDTH+4;
        }

        nowwpixel += NUM_WIDTH-4;
    }
    dest = boxmemorie + MOVE_HPIXEL * WINDOW_WIDTH + MOVE_WPIXEL;
    for (j=0;j<TEXT_HEIGHT;j++)
    {
        for (k=0;k<TEXT_WIDTH;k++)
        {
            (*dest) = boxmoveimage[j][k]?color:0;
            dest ++;
        }
        dest += WINDOW_WIDTH - TEXT_WIDTH;
    }
}

void boxrenderwin()
{
    int* dest;
    int j,k;
    if (boxhaswin)
    {
        dest = boxmemorie + WIN_HPIXEL * WINDOW_WIDTH + WIN_WPIXEL;
        for (j=0;j<WIN_HEIGHT;j++)
        {
            for (k=0;k<WIN_WIDTH;k++)
            {
                (*dest) = boxwinimage[j][k];
                dest ++;
            }
            dest += WINDOW_WIDTH - WIN_WIDTH;
        }
    } else
    {
        dest = boxmemorie + WIN_HPIXEL * WINDOW_WIDTH + WIN_WPIXEL;
        for (j=0;j<WIN_HEIGHT;j++)
        {
            for (k=0;k<WIN_WIDTH;k++)
            {
                (*dest) = 0;
                dest ++;
            }
            dest += WINDOW_WIDTH - WIN_WIDTH;
        }
    }
}

int boxoutputelement( int x, int y )
{
	int	i, j;
	int	*dest;
	switch ( boxmap[x][y] )
	{
	case -1:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxoutside[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 1:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxwall[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 3:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxman[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 2:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxnormalbox[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 4:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxdestpoint[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 0:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxfloor[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 5:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
                (*dest) = boxrightbox[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;

	case 6:
        dest = boxmemorie + x * WINDOW_WIDTH * ELEMENT_HEIGHT + y * ELEMENT_WIDTH + BEGIN_PIXEL;
		for ( i = 0; i < ELEMENT_HEIGHT; i++ )
		{
			for ( j = 0; j < ELEMENT_WIDTH; j++ )
			{
				(*dest) = boxman[i][j];
				dest++;
			}
			dest += WINDOW_WIDTH - ELEMENT_WIDTH;
		}
		break;
	}
	return(0);
}


int boxfindman()
{
	int i, j;
	for ( i = 0; i < BOARD_HEIGHT; i++ )
		for ( j = 0; j < BOARD_WIDTH; j++ )
		{
			if ( boxmap[i][j] == 3 || boxmap[i][j] == 6 )
			{
                boxmanx = i; boxmany = j; return(0);
			}
		}
	return(0);
}


int boxcount1()
{
	int	n = 0;
	int	i, j;
	for ( i = 0; i < BOARD_HEIGHT; i++ )
		for ( j = 0; j < BOARD_WIDTH; j++ )
		{
            if ( boxmap[i][j] >=4)
				n++;
		}
	return(n);
}


int boxcount2()
{
	int	m = 0;
	int	i, j;
	for ( i = 0; i < BOARD_HEIGHT; i++ )
		for ( j = 0; j < BOARD_WIDTH; j++ )
		{
			if ( boxmap[i][j] == 5 )
				m++;
		}
	return(m);
}


void boxrestartgame()
{
    int i, j;
    for ( i = 0; i < WINDOW_SIZE; i++ )
        boxmemorie[i] = 0;
    boxhaswin = 0;
    boxmovements.clear();
	for ( i = 0; i < BOARD_HEIGHT; i++ )
		for ( j = 0; j < BOARD_WIDTH; j++ )
			boxmap[i][j] = -1;
    int nowheight=boxlevelheight[boxnowlevel];
    int nowwidth=boxlevelwidth[boxnowlevel];
    for ( i = 0; i < nowheight; i++ )
        for ( j = 0; j < nowwidth; j++ )
            boxmap[boxgetposition[nowheight] + i][boxgetposition[nowwidth] + j] = boxlevel[boxnowlevel][i][j];
    for ( i = 0; i < BOARD_HEIGHT; i++ )
        for ( j = 0; j < BOARD_WIDTH; j++ )
            if (boxmap[i][j]!=-1)
                boxoutputelement( i, j );
    boxrequiredtowin = boxcount1();
    boxfindman();
    boxrenderlevel();
    boxrendermovement();
    boxrenderwin();
}

void boxnextlevel()
{
    if (boxnowlevel==99) boxnowlevel=0; else boxnowlevel ++;
    boxrestartgame();
}
void boxpreviouslevel()
{
    if (boxnowlevel) boxnowlevel--; else boxnowlevel=99;
    boxrestartgame();
}

void boxbegingame( int* address )
{
    boxnowlevel=0;
    boxmemorie = address;
    boxrestartgame();
}


int boxgoup()
{
    if ( boxmap[boxmanx][boxmany] == 3 || boxmap[boxmanx][boxmany] == 6 )
	{
        int status = (boxmap[boxmanx][boxmany]==3)?0:4;
        if ( boxmanx - 1 >= 0 && boxmap[boxmanx - 1][boxmany] == 0 )
		{
            boxmap[boxmanx - 1][boxmany]	= 3;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx - 1, boxmany );
            boxmanx -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx - 1 >= 0 && boxmap[boxmanx - 1][boxmany] == 4 )
		{
            boxmap[boxmanx - 1][boxmany]	= 6;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx - 1, boxmany );
            boxmanx -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx - 2 >= 0 && boxmap[boxmanx - 1][boxmany] == 2 && boxmap[boxmanx - 2][boxmany] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx - 1][boxmany]	= 3;
            boxmap[boxmanx - 2][boxmany]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx - 1, boxmany );
            boxoutputelement( boxmanx - 2, boxmany );
            boxmanx -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx - 2 >= 0 && boxmap[boxmanx - 1][boxmany] == 2 && boxmap[boxmanx - 2][boxmany] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx - 1][boxmany]	= 3;
            boxmap[boxmanx - 2][boxmany]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx - 1, boxmany );
            boxoutputelement( boxmanx - 2, boxmany );
            boxmanx -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx - 2 >= 0 && boxmap[boxmanx - 1][boxmany] == 5 && boxmap[boxmanx - 2][boxmany] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx - 1][boxmany]	= 6;
            boxmap[boxmanx - 2][boxmany]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx - 1, boxmany );
            boxoutputelement( boxmanx - 2, boxmany );
            boxmanx -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx - 2 >= 0 && boxmap[boxmanx - 1][boxmany] == 5 && boxmap[boxmanx - 2][boxmany] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx - 1][boxmany]	= 6;
            boxmap[boxmanx - 2][boxmany]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx - 1, boxmany );
            boxoutputelement( boxmanx - 2, boxmany );
            boxmanx -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
	}
	return(0);
}


int boxgodown()
{
    if ( boxmap[boxmanx][boxmany] == 3 || boxmap[boxmanx][boxmany] == 6 )
	{
        int status = (boxmap[boxmanx][boxmany]==3)?0:4;
        if ( boxmanx + 1 < BOARD_HEIGHT && boxmap[boxmanx + 1][boxmany] == 0 )
		{
            boxmap[boxmanx + 1][boxmany]	= 3;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx + 1, boxmany );
            boxmanx += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx + 1 < BOARD_HEIGHT && boxmap[boxmanx + 1][boxmany] == 4 )
		{
            boxmap[boxmanx + 1][boxmany]	= 6;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx + 1, boxmany );
            boxmanx += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx + 2 < BOARD_HEIGHT && boxmap[boxmanx + 1][boxmany] == 2 && boxmap[boxmanx + 2][boxmany] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx + 1][boxmany]	= 3;
            boxmap[boxmanx + 2][boxmany]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx + 1, boxmany );
            boxoutputelement( boxmanx + 2, boxmany );
            boxmanx += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx + 2 < BOARD_HEIGHT && boxmap[boxmanx + 1][boxmany] == 2 && boxmap[boxmanx + 2][boxmany] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx + 1][boxmany]	= 3;
            boxmap[boxmanx + 2][boxmany]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx + 1, boxmany );
            boxoutputelement( boxmanx + 2, boxmany );
            boxmanx += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx + 2 < BOARD_HEIGHT && boxmap[boxmanx + 1][boxmany] == 5 && boxmap[boxmanx + 2][boxmany] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx + 1][boxmany]	= 6;
            boxmap[boxmanx + 2][boxmany]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx + 1, boxmany );
            boxoutputelement( boxmanx + 2, boxmany );
            boxmanx += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmanx + 2 < BOARD_HEIGHT && boxmap[boxmanx + 1][boxmany] == 5 && boxmap[boxmanx + 2][boxmany] == 0 )
		{
            boxmap[boxmanx][boxmany]	= 0;
            boxmap[boxmanx + 1][boxmany]	= 6;
            boxmap[boxmanx + 2][boxmany]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx + 1, boxmany );
            boxoutputelement( boxmanx + 2, boxmany );
            boxmanx += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
	}
	return(0);
}


int boxgoleft()
{
    if ( boxmap[boxmanx][boxmany] == 3 || boxmap[boxmanx][boxmany] == 6 )
	{
        int status = (boxmap[boxmanx][boxmany]==3)?0:4;
        if ( boxmany - 1 >= 0 && boxmap[boxmanx][boxmany - 1] == 0 )
		{
            boxmap[boxmanx][boxmany - 1]	= 3;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany - 1 );
            boxmany -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany - 1 >= 0 && boxmap[boxmanx][boxmany - 1] == 4 )
		{
            boxmap[boxmanx][boxmany - 1]	= 6;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany - 1 );
            boxmany -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany - 2 >= 0 && boxmap[boxmanx][boxmany - 1] == 2 && boxmap[boxmanx][boxmany - 2] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany - 1]	= 3;
            boxmap[boxmanx][boxmany - 2]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany - 1 );
            boxoutputelement( boxmanx, boxmany - 2 );
            boxmany -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany - 2 >= 0 && boxmap[boxmanx][boxmany - 1] == 2 && boxmap[boxmanx][boxmany - 2] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany - 1]	= 3;
            boxmap[boxmanx][boxmany - 2]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany - 1 );
            boxoutputelement( boxmanx, boxmany - 2 );
            boxmany -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany - 2 >= 0 && boxmap[boxmanx][boxmany - 1] == 5 && boxmap[boxmanx][boxmany - 2] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany - 1]	= 6;
            boxmap[boxmanx][boxmany - 2]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany - 1 );
            boxoutputelement( boxmanx, boxmany - 2 );
            boxmany -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany - 2 >= 0 && boxmap[boxmanx][boxmany - 1] == 5 && boxmap[boxmanx][boxmany - 2] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany - 1]	= 6;
            boxmap[boxmanx][boxmany - 2]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany - 1 );
            boxoutputelement( boxmanx, boxmany - 2 );
            boxmany -= 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
	}
	return(0);
}


int boxgoright()
{
    if ( boxmap[boxmanx][boxmany] == 3 || boxmap[boxmanx][boxmany] == 6 )
	{
        int status = (boxmap[boxmanx][boxmany]==3)?0:4;
        if ( boxmany + 1 < BOARD_WIDTH && boxmap[boxmanx][boxmany + 1] == 0 )
		{
            boxmap[boxmanx][boxmany + 1]	= 3;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany + 1 );
            boxmany += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany + 1 < BOARD_WIDTH && boxmap[boxmanx][boxmany + 1] == 4 )
		{
            boxmap[boxmanx][boxmany + 1]	= 6;
            boxmap[boxmanx][boxmany]	= status;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany + 1 );
            boxmany += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany + 2 < BOARD_WIDTH && boxmap[boxmanx][boxmany + 1] == 2 && boxmap[boxmanx][boxmany + 2] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany + 1]	= 3;
            boxmap[boxmanx][boxmany + 2]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany + 1 );
            boxoutputelement( boxmanx, boxmany + 2 );
            boxmany += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany + 2 < BOARD_WIDTH && boxmap[boxmanx][boxmany + 1] == 2 && boxmap[boxmanx][boxmany + 2] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany + 1]	= 3;
            boxmap[boxmanx][boxmany + 2]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany + 1 );
            boxoutputelement( boxmanx, boxmany + 2 );
            boxmany += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany + 2 < BOARD_WIDTH && boxmap[boxmanx][boxmany + 1] == 5 && boxmap[boxmanx][boxmany + 2] == 4 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany + 1]	= 6;
            boxmap[boxmanx][boxmany + 2]	= 5;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany + 1 );
            boxoutputelement( boxmanx, boxmany + 2 );
            boxmany += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
        if ( boxmany + 2 < BOARD_WIDTH && boxmap[boxmanx][boxmany + 1] == 5 && boxmap[boxmanx][boxmany + 2] == 0 )
		{
            boxmap[boxmanx][boxmany]	= status;
            boxmap[boxmanx][boxmany + 1]	= 6;
            boxmap[boxmanx][boxmany + 2]	= 2;
            boxoutputelement( boxmanx, boxmany );
            boxoutputelement( boxmanx, boxmany + 1 );
            boxoutputelement( boxmanx, boxmany + 2 );
            boxmany += 1;

            boxmovements.add();
            boxrendermovement();
			return(0);
		}
	}
	return(0);
}


void boxkeypress( char key )
{
	int nowcount;
    if ( !boxhaswin )
	{
		switch ( key )
		{
        case 'W': boxgoup(); break;
        case 'S': boxgodown(); break;
        case 'A': boxgoleft(); break;
        case 'D': boxgoright(); break;
        case 'R': boxrestartgame(); break;
        case '9': boxnextlevel(); break;
        case '0': boxpreviouslevel(); break;
		}
        nowcount = boxcount2();
        if ( boxrequiredtowin == nowcount )
		{
            boxhaswin = 1;
            boxrenderwin();
		}
	}else  {
		switch ( key )
		{
        case 'R': boxrestartgame(); break;
        case '9': boxnextlevel(); break;
        case '0': boxpreviouslevel(); break;
        }
	}
}


#endif /* BOX_H */
