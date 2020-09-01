#ifndef ZUOBIAO_H
#define ZUOBIAO_H

struct zuobiao{
    int x,y;
    zuobiao *last;
    zuobiao *next;
};

static int nextlocation[4][2]={-1,0,1,0,0,-1,0,1};
#endif // ZUOBIAO_H
