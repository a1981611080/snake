#ifndef GAMEWEIGHT_H
#define GAMEWEIGHT_H

#include <QWidget>
#include "QMessageBox"
#include <QDebug>
#include <QTimer>
#include <QImage>
#include "upqp.h"
#include "help.h"
#include "snake.h"
#include "gluttonoussnake.h"
#include "zuobiao.h"
#include "seed.h"
#include "util.h"
namespace Ui {
class gameweight;
}

class gameweight : public QWidget
{
    Q_OBJECT

public:
    explicit gameweight(QWidget *parent = nullptr,QWidget *last=nullptr,bool single=false);
    ~gameweight();


private slots:
    void on_bangzhu_clicked();

    void on_paihang_clicked();

private:
    Ui::gameweight *ui;

private:
    int map[75][55];
    void initui();
    void initData();
    void closeEvent(QCloseEvent*);
    void showhelp();
    void paintEvent(QPaintEvent *event);
    void signconnect();//信号连接
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void sheyi1(QKeyEvent *event);
    void sheyi2(QKeyEvent *event);
    void jiesu();

private:
    QWidget *last;
    upQp *kaishi;
    void kaishi_c();
    upQp *zhanting;
    void zhanting_c();
    help *he;
    int shuaxin;
    snake *_1p=NULL;
    snake *_2p=NULL;
    seed * dian;
    bool test=false;
    bool tongbu1;//同步按键和画图
    bool tongbu2;//同步按键和画图
    bool single;
    int _1pscore=0;
    int _2pscore=0;

//画图
private:
    inline void drawbeijing(QPainter &p);
    inline void draw1p(QPainter &p);
    inline void draw2p(QPainter &p);
    void drawseed(QPainter &p);
    int x=40,y=40;
private://参数
    int r=5;//半径
    int map_up=30;
    int map_down=730;
    int map_left=40;
    int map_rigtht=510;
    int ms = 100;
    bool end;
private slots:
    void die(int no);
    void peng(int x,int y,int no);

signals:
void diedui();

};

#endif // GAMEWEIGHT_H
