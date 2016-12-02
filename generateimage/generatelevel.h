#ifndef GENERATELEVEL_H
#define GENERATELEVEL_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;
void generatelevel(string filename)
{
    FILE*f = fopen(filename.c_str(),"r");
    FILE*g = fopen("d:\\image\\level.txt","w");
    char s[20000];
    int t[100][15][15];
    int wi[100],hi[100];
    for (int gk=0;gk<100;gk++)
    {
        if (gk==99)
        {
            cout<<"das"<<endl;
        }
        fgets(s,200,f);
        cout<<s<<endl;
        fgets(s,200,f);
        s[strlen(s)-1]='\0';
        int width=0,height=0;
        for (int i=0;i<15;i++)
            for (int j=0;j<15;j++)
                t[gk][i][j]=-1;
        while (strlen(s)!=0)
        {
            if (width==0) width = strlen(s);

            bool haschar=false;
            for (int i=0;i<strlen(s);i++)
            {
                switch (s[i])
                {
                case ' ':
                    if (haschar) t[gk][height][i]=0; else t[gk][height][i]=-1; break;
                case '@':
                    t[gk][height][i]=3; haschar=true; break;
                case '#':
                    t[gk][height][i]=1; haschar=true; break;
                case '+':
                    t[gk][height][i]=6; haschar=true; break;
                case '$':
                    t[gk][height][i]=2; haschar=true; break;
                case '.':
                    t[gk][height][i]=4; haschar=true; break;
                case '*':
                    t[gk][height][i]=5; haschar=true; break;
                }
            }
            for (int i=strlen(s)-1;i>=0;i--)
                if (t[gk][height][i]==0) t[gk][height][i]=-1;
                else break;
            height++;
            fgets(s,200,f);
            s[strlen(s)-1]='\0';
        }
        wi[gk]=width; hi[gk]=height;
    }
    fclose(f);
    fprintf(g,"static const int boxlevel[100][15][15]={");
    for (int i=0;i<100;i++)
    {
        fprintf(g,"{");
        for (int j=0;j<15;j++)
        {
            fprintf(g,"{");
            for (int k=0;k<15;k++)
            {
                fprintf(g,"%d",t[i][j][k]);
                if (k!=14) fprintf(g,",");
            }
            fprintf(g,"}");
            if (j!=14) fprintf(g,",");
        }
        fprintf(g,"}");
        if (i!=99) fprintf(g,",");
    }
    fprintf(g,"};\n");

    fprintf(g,"static const int boxlevelwidth[100]={");
    for (int i=0;i<100;i++)
    {
        fprintf(g,"%d",wi[i]);
        if (i!=99) fprintf(g,",");
    }
    fprintf(g,"};\n");

    fprintf(g,"static const int boxlevelheight[100]={");
    for (int i=0;i<100;i++)
    {
        fprintf(g,"%d",hi[i]);
        if (i!=99) fprintf(g,",");
    }
    fprintf(g,"};\n");

    fclose(g);
    cout<<hi[99]<<' '<<wi[99]<<endl;
}

#endif // GENERATELEVEL_H
