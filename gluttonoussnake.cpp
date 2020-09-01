#include "gluttonoussnake.h"
#include "ui_gluttonoussnake.h"

GluttonousSnake::GluttonousSnake(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GluttonousSnake)
{
    ui->setupUi(this);
    //初始化界面
    initui();
    //信号连接
    signConnect();
}

GluttonousSnake::~GluttonousSnake()
{
    delete ui;
}

void GluttonousSnake::initui(){
    //单选按钮处理
//    chose.addButton(ui->_1);
//    chose.addButton(ui->_2);
    //标签
    ui->double_game->setText(_L3);
    ui->single_game->setText(_L2);
    ui->title->setText(_L1);
    //标题
    this->setWindowTitle("贪吃蛇");
    //按钮
    ui->Bexit->setText(_L5);
    ui->Bstart->setText(_L4);
    ui->Bstart->setEnabled(false);
    //窗口大小
    this->setFixedSize(493,257);

}

void GluttonousSnake::signConnect(){
    connect(ui->Bexit,&QPushButton::released,[this](){this->close();});
     connect(ui->Bstart,&QPushButton::released,[this](){this->start();});
     connect(ui->_1,&QRadioButton::toggled,[this](){this->ui->Bstart->setEnabled(true);});
     connect(ui->_2,&QRadioButton::toggled,[this](){this->ui->Bstart->setEnabled(true);});
}

void GluttonousSnake::start(){
    if(this->ui->_1->isChecked())  gameStart = new gameweight(nullptr,this,true);
    else gameStart = new gameweight(nullptr,this,false);
    gameStart->show();
    this->setVisible(false);
}

void GluttonousSnake::closeEvent ( QCloseEvent * event){

}
