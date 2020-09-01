#include "seed.h"
#include <QtGlobal>

seed::seed(QObject *parent) : QObject(parent)
{
    qsrand(0);


}

void seed::setMap(int(*map1)[55])
{
    this->map=map1;
}

void seed::add(zuobiao *cc)
{
    if(cc==NULL) return;
    if(seedHead==NULL){
        seedHead=cc;
        mapzhuan(map,cc->x,cc->y)=3;
        return;
    }
    zuobiao *temp = seedHead;

    while(temp->next!=NULL) temp=temp->next;
    temp->next=cc;
    cc->last=temp;
    temp=cc;
    while(temp!=NULL){
        mapzhuan(map,temp->x,temp->y)=3;
        temp=temp->next;
    }
}

void seed::del(int x,int y)
{
    zuobiao *temp = seedHead;
    while (temp->x!=x||temp->y!=y) {
        temp=temp->next;
    }
    mapzhuan(map,x,y)=0;
    //只有唯一一个时
    if(temp->last==NULL&&temp->next==NULL){
        delete temp;
        seedHead=NULL;
        shengcheng();
        return;
    }
    //末尾处理
    else if(temp->next==NULL)
    {
        temp->last->next=NULL;
        delete temp;
        return;
    }
    //首位处理
    else if(temp->last==NULL)
    {
        seedHead=temp->next;
        seedHead->last=NULL;
        delete temp;
        return;
    }
    //中间处理
    else
    {
        temp->last->next=temp->next;
        temp->next->last=temp->last;
        delete temp;
        return;
    }
}

void seed::shengcheng()
{
    int x = qrand()%69;
    int y = qrand()%45;
    while(map[x][y]!=0){
        x = qrand()%69;
        y = qrand()%45;
    }
    zuobiao *temp = new zuobiao;
    int* temp1 =maphui(x,y);
    temp->x=temp1[0];
    temp->y=temp1[1];
    temp->next=NULL;
    temp->last=NULL;
    delete temp1;
    add(temp);
}

zuobiao* seed::getseed()
{
    return seedHead;
}
