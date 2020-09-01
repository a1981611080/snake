#include "snake.h"
#include <QDebug>
//snake::snake() :
//{

//}
void snake::addData()
{
   zuobiao *temp = new zuobiao;
   temp->x=lasttail.x;
   temp->y=lasttail.y;
   temp->last=snakeTail;
   temp->next=NULL;
   snakeTail->next=temp;
   snakeTail=temp;
}

void snake::runData()
{
    lasttail.x=snakeTail->x;
    lasttail.y=snakeTail->y;
    mapzhuan(map,lasttail.x,lasttail.y)=0;
    zuobiao *temp=new zuobiao;
    temp->x=snakeHead->x+nextlocation[location][0]*r*2;
    temp->y=snakeHead->y+nextlocation[location][1]*r*2;
    if(temp->x==limit[1]+2*r) temp->x=limit[0];
    else if(temp->x==limit[0]-2*r) temp->x=limit[1];
    if(temp->y==limit[3]+2*r) temp->y=limit[2];
    else if(temp->y==limit[2]-2*r) temp->y=limit[3];

    if( mapzhuan(map,temp->x,temp->y) != 0)
    {
        emit yao(temp->x,temp->y,no);
    }
    //连接头部
    temp->last=NULL;
    temp->next=snakeHead;
    snakeHead->last=temp;
    snakeHead=temp;
    mapzhuan(map,snakeHead->x,snakeHead->y)=no;
    //释放尾部
    temp=snakeTail->last;
    temp->next=NULL;
    free(snakeTail);
    snakeTail=temp;




}

void snake::changeLocation(const int temp)
{
    location=temp;
}

zuobiao* snake::delData(int x,int y)
{
    zuobiao *temp=snakeHead;
    while(true)
    {
        if(temp->x==x&&temp->y==y)
        {
            temp->last->next=NULL;
            snakeTail=temp->last;
            zuobiao* temp1=temp->next;
            temp->last=NULL;
            delete temp;
            return temp1;
        }
        else
        {
         temp=temp->next;
        }
    }
}

snake::snake(int x,int y,int &r,int no,QObject *parent):r(r),no(no),QObject(parent)
{
    snakeHead=new zuobiao;
    snakeHead->x=x;
    snakeHead->y=y;
    snakeHead->last=NULL;
    snakeHead->next=NULL;
    snakeTail=snakeHead;
}

void snake::setMap(int(*map)[55])
{
    this->map=map;
    qDebug()<<map[4][4];

}

zuobiao* snake::getHead()
{
    return snakeHead;
}

void snake::run()
{
    runData();
}

void snake::chidao()
{
    addData();
}

int snake::getLocation()
{
    return location;
}

void snake::setR(int &r)
{
    this->r=r;
}

void snake::setlimit(int up,int down,int left,int right)
{
    limit[0]=up;
    limit[1]=down;
    limit[2]=left;
    limit[3]=right;
}

snake::~snake()
{
 zuobiao* temp=snakeHead;
 zuobiao*temp1;
 while(temp!=NULL)
 {
     temp1=temp->next;
     delete temp;
     temp=temp1;
 }
 qDebug()<<"die ojk";
}

int snake::getNO()
{
    return no;
}
int snake::getLegth()
{
    int legth=0;
    for(zuobiao* i=snakeHead;i!=NULL;i=i->next)
    {
        legth++;
    }
    return legth;
}
