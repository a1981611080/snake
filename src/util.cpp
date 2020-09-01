#include "util.h"
int& mapzhuan(int(*map)[55],int x,int y)
{
    return map[(x-30)/10][(y-40)/10];
}

int* maphui(int x,int y)
{
    int * p = new int[2];
    p[0]=x*10+30;
    p[1]=y*10+40;
    return p;

}
