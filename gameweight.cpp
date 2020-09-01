 #include "gameweight.h"
#include "ui_gameweight.h"
#include<QDialog>
#include <QPainter>
#include <QDebug>


gameweight::gameweight(QWidget *parent,QWidget *last,bool single) :
    QWidget(parent),
    ui(new Ui::gameweight)
{

    setAttribute(Qt::WA_DeleteOnClose);
    this->single=single;
    qDebug()<<single;
    ui->setupUi(this);
    this->last=last;
    initui();
    signconnect();


}

gameweight::~gameweight()
{
    delete kaishi;//开始按钮
    delete zhanting;//暂停按钮
    delete ui;
    delete _1p;//1p蛇
}

void gameweight::initui(){
   //标题
    this->setWindowTitle("贪吃蛇");
    //窗口大小
    this->setFixedSize(787,869);
    //按钮初始化
    ui->paihang->setText(_L8);
    ui->bangzhu->setText(_L9);
    //特殊按钮
    kaishi = new upQp(_L12,_L13,this);
    kaishi->setFixedSize(151,61);
    kaishi->move(572,763);
    kaishi->setFocusPolicy(Qt::NoFocus);
    zhanting = new upQp(_L10,_L11,this);
    zhanting->setFixedSize(221,61);
    zhanting->setMerry(kaishi);
    zhanting->move(190,763);
    zhanting->setFocusPolicy(Qt::NoFocus);
    //标签
    ui->p1->setText(_L6);

    if(!single)
    {
    ui->p2->setText(_L7);
    ui->p2Score->setText("0");
    }
}

void gameweight::closeEvent ( QCloseEvent * e ){

    //退出窗口
    if( QMessageBox::question(this,
                                 tr(_L22),
                                 tr(_L23),
                                 tr(_L24), tr(_L25) )
                       == 0){
            last->show();
            e->accept();//不会将事件传递给组件的父组件

        }
        else
          e->ignore();

}
void gameweight::showhelp()
{
    he=new help();
    he->setWindowModality(Qt::ApplicationModal);
    he->setAttribute(Qt::WA_QuitOnClose,true);
    he->setFixedSize(400,300);
    he->show();
}

void gameweight::on_bangzhu_clicked()
{
    showhelp();
}

void gameweight::paintEvent(QPaintEvent *event)
{
 //画背景
 QPainter p(this);
 drawbeijing(p);//画背景
 if(_1p!=NULL)draw1p(p);//画1p
 if(!single) if(_2p!=NULL)draw2p(p);
 drawseed(p);//c
}

void gameweight::signconnect()
{

    connect(kaishi,&QPushButton::released,this,&gameweight::kaishi_c);
    connect(zhanting,&QPushButton::released,this,&gameweight::zhanting_c);
}

void gameweight::drawbeijing(QPainter &p)
{
    QPen qp;
    qp.setColor(Qt::white);
    QBrush qb;
    qb.setColor(Qt::white);
    qb.setStyle(Qt::SolidPattern);
    p.setBrush(qb);
    p.setPen(qp);
    p.drawRect(30,20,490,720);
    ui->p1Score->setText(QString::number(_1pscore));
    if(!single)ui->p2Score->setText(QString::number(_2pscore));
}

void gameweight::draw1p(QPainter &p)
{
    QPen qp;
    qp.setColor(Qt::red);
    QBrush qb;
    qb.setColor(Qt::red);
    qb.setStyle(Qt::SolidPattern);
    p.setBrush(qb);
    p.setPen(qp);
    if(kaishi->getZhuantai()!=false)
    if(_1p!=NULL)
    {
    zuobiao *temp=_1p->getHead();


    while (temp!=NULL) {
        p.drawEllipse(QPoint(temp->y,temp->x),r,r);
        temp=temp->next;

    }
    }


}

void gameweight::drawseed(QPainter &p)
{
    QPen qp;
    qp.setColor(Qt::green);
    QBrush qb;
    qb.setColor(Qt::green);
    qb.setStyle(Qt::SolidPattern);
    p.setBrush(qb);
    p.setPen(qp);
    if(kaishi->getZhuantai()!=false)
    if(dian!=NULL)
    {
    zuobiao *temp=dian->getseed();


    while (temp!=NULL) {
        p.drawEllipse(QPoint(temp->y,temp->x),r,r);
        temp=temp->next;

    }
    }

}

void gameweight::keyPressEvent(QKeyEvent *event)
{
   if(tongbu1)
   {
   sheyi1(event);
   tongbu1=false;
   }
   if(!single)if(tongbu2)
   {
       sheyi2(event);
       tongbu2=false; 
   }
}

void gameweight::initData()
{
    memset(map,0,sizeof(map));
    end=false;
    delete _1p;

    _1p=new snake(100,300,r,1,this);
    _1pscore=0;
    _1p->setMap(map);
    _1p->setR(r);
    _1p->setlimit(map_up,map_down,map_left,map_rigtht);
    connect(_1p,SIGNAL(yao(int,int,int)),this,SLOT(peng(int,int,int)));
    
    if(!single)
    {
        delete _2p;
        _2p=new snake(700,100,r,2,this);
        _2pscore=0;
        _2p->setMap(map);
        _2p->setR(r);
        _2p->setlimit(map_up,map_down,map_left,map_rigtht);
        connect(_2p,SIGNAL(yao(int,int,int)),this,SLOT(peng(int,int,int))); 
    }
     
    dian=new seed(this);
    dian->setMap(map);
    dian->shengcheng();
    shuaxin=startTimer(ms);

}

void gameweight::timerEvent(QTimerEvent *event)
{

    if(event->timerId()==shuaxin)//每过一秒完成的事
    {

        if(_1p!=NULL)
        {
        _1p->run();
        tongbu1=true;
        }
        if(!single)if(_2p!=NULL&&!end)
        {
            _2p->run();
            tongbu2=true;
        }
    }
        if(!end)update();
}

void gameweight::sheyi1(QKeyEvent *event)
{
    if(single)//单人按键
    {
    if(event->key()==Qt::Key_Right)
    {
        if(_1p->getLocation()!=snake::RUN_LEFT)

        _1p->changeLocation(snake::RUN_RIGHT);
    }
    if(event->key()==Qt::Key_Left)
    {
        if(_1p->getLocation()!=snake::RUN_RIGHT)
        _1p->changeLocation(snake::RUN_LEFT);
    }
    if(event->key()==Qt::Key_Up)
    {
        if(_1p->getLocation()!=snake::RUN_DOWN)
       _1p->changeLocation(snake::RUN_UP);
    }
    if(event->key()==Qt::Key_Down)
    {
        if(_1p->getLocation()!=snake::RUN_UP)
        _1p->changeLocation(snake::RUN_DOWN);
    }
    }
    //双人时的操作
    else
    {
        if(event->key()==Qt::Key_D)
        {
            if(_1p->getLocation()!=snake::RUN_LEFT)
    
            _1p->changeLocation(snake::RUN_RIGHT);
        }
        if(event->key()==Qt::Key_A)
        {
            if(_1p->getLocation()!=snake::RUN_RIGHT)
            _1p->changeLocation(snake::RUN_LEFT);
        }
        if(event->key()==Qt::Key_W)
        {
            if(_1p->getLocation()!=snake::RUN_DOWN)
           _1p->changeLocation(snake::RUN_UP);
        }
        if(event->key()==Qt::Key_S)
        {
            if(_1p->getLocation()!=snake::RUN_UP)
            _1p->changeLocation(snake::RUN_DOWN);
        }
    }
}

void gameweight::jiesu()
{
    killTimer(shuaxin);
    end=true;
    disconnect(_1p,SIGNAL(yao(int,int,int)),this,SLOT(peng(int,int,int)));
     _1pscore=0;
    if(!single)
    {
        disconnect(_2p,SIGNAL(yao(int,int,int)),this,SLOT(peng(int,int,int)));
        _2pscore=0;
    }

}

void gameweight::die(int no)
{
    if(no==1)
    QMessageBox::question(this,
                                     tr("警告"),
                                     tr("1P死了"),
                                     tr("确认") );
    if(no==2)
    QMessageBox::question(this,
                                     tr("警告"),
                                     tr("2P死了"),
                                     tr("确认") );
    kaishi->trychange();
    jiesu();
}
void gameweight::on_paihang_clicked()
{
    update();
}

void gameweight::kaishi_c()
{
    bool zhuantai = kaishi->getZhuantai();
    if(!zhuantai)
    {
       initData();

    }
    else
    {
        jiesu();

    }
    kaishi->trychange();
}

void gameweight::zhanting_c()
{
bool zhuantai = zhanting->getZhuantai();
if(!zhuantai)
{
   killTimer(shuaxin);

}
else
{
   shuaxin = startTimer(ms);

}
zhanting->trychange();
}


void gameweight::peng(int x,int y,int no)
{

    //已经转好了
    if(single)//单人模式
    {
    if(mapzhuan(map,x,y)==no) die(no);
    else if(mapzhuan(map,x,y)==3){

            _1p->chidao();
            _1pscore+=5;
        dian->del(x,y);

    }
    }
    else{
        if(mapzhuan(map,x,y)==3)//吃豆豆
        {
            dian->del(x,y);
            if(no==1)//1p吃到
            {
                _1p->chidao();
                _1pscore+=5;
            }
            if(no==2)
            {
                _2p->chidao();
                _2pscore+=5;
            }

        }
        else
        {
            //吃到头部
            if(x==_1p->getHead()->x&&y==_1p->getHead()->y || x==_2p->getHead()->x&&y==_2p->getHead()->y)
            {
                int l1 = _1p->getLegth();
                int l2 = _2p->getLegth();
                if(l1>l2)
                {
                    QMessageBox::question(this,
                                                     tr("警告"),
                                                     tr("2P死了"),
                                                     tr("确认") );
                }
                else if(l1<l2)
                {
                    QMessageBox::question(this,
                                                     tr("警告"),
                                                     tr("1P死了"),
                                                     tr("确认") );
                }
                else
                {
                    QMessageBox::question(this,
                                                     tr("警告"),
                                                     tr("都死了"),
                                                     tr("确认") );
                }
                kaishi->trychange();
                jiesu();

            }

            //吃到自己
            else if(no==mapzhuan(map,x,y))
            {
                if(no==1)
                {
                    QMessageBox::question(this,
                                                     tr("警告"),
                                                     tr("1P死了"),
                                                     tr("确认") );
                }
                else if(no==2)
                {
                    QMessageBox::question(this,
                                                     tr("警告"),
                                                     tr("2P死了"),
                                                     tr("确认") );
                }
                jiesu();
            }
            else
            {
                int eatno=mapzhuan(map,x,y);
                if(eatno==1)
                {
                    dian->add(_1p->delData(x,y));
                }
                else if(eatno==2)
                {
                    dian->add(_2p->delData(x,y));
                }
            }
        }

        }



}

void gameweight::sheyi2(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Right)
    {
        if(_2p->getLocation()!=snake::RUN_LEFT)

        _2p->changeLocation(snake::RUN_RIGHT);
    }
    if(event->key()==Qt::Key_Left)
    {
        if(_2p->getLocation()!=snake::RUN_RIGHT)
        _2p->changeLocation(snake::RUN_LEFT);
    }
    if(event->key()==Qt::Key_Up)
    {
        if(_2p->getLocation()!=snake::RUN_DOWN)
       _2p->changeLocation(snake::RUN_UP);
    }
    if(event->key()==Qt::Key_Down)
    {
        if(_2p->getLocation()!=snake::RUN_UP)
        _2p->changeLocation(snake::RUN_DOWN);
    }
}

void gameweight::draw2p(QPainter &p)
{
    QPen qp;
    qp.setColor(Qt::blue);
    QBrush qb;
    qb.setColor(Qt::blue);
    qb.setStyle(Qt::SolidPattern);
    p.setBrush(qb);
    p.setPen(qp);
    if(kaishi->getZhuantai()!=false)
    if(_2p!=NULL)
    {
    zuobiao *temp=_2p->getHead();


    while (temp!=NULL) {
        p.drawEllipse(QPoint(temp->y,temp->x),r,r);
        temp=temp->next;

    }
    }
}
