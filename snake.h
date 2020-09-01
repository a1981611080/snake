#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include "zuobiao.h"
#include "util.h"
class snake : public QObject
{


    Q_OBJECT
public:

//    explicit snake(QObject *parent = nullptr);
private:
    int limit[4];//上下左右范围
    int location=0;//0上1下2左3右
    int(*map)[55];
    zuobiao * snakeHead;//头指针
    zuobiao * snakeTail;
    zuobiao lasttail;
    int &r;//半径
    int no;
public:
    static const int RUN_UP=0;
    static const int RUN_DOWN=1;
    static const int RUN_LEFT=2;
    static const int RUN_RIGHT=3;

public:

    void changeLocation(const int); //改变方向
    void run();//运行
    void setR(int &r);
    int getNO();
    int getLegth();
    explicit snake(int x,int y,int &r,int no,QObject *parent = nullptr);
    void setMap(int(*map)[55]);
    zuobiao* getHead();
    void chidao();
    int getLocation();
    void setlimit(int up,int down,int left,int right);
    zuobiao* delData(int x,int y);
    zuobiao* delData(zuobiao temp);
    ~snake();

//核心算法
private:
    void addData();

    void runData();
signals:
    void yao(int x,int y,int no);

};

#endif // SNAKE_H
