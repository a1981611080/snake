#ifndef GLUTTONOUSSNAKE_H
#define GLUTTONOUSSNAKE_H

#include <QWidget>
#include <gameweight.h>
#include <QDebug>
#include <QButtonGroup>
#include "const_string.h"
#include <QEvent>
#include<QCloseEvent>
QT_BEGIN_NAMESPACE
class gameweight;
namespace Ui { class GluttonousSnake; }
QT_END_NAMESPACE

class GluttonousSnake : public QWidget
{
    Q_OBJECT

public:
    GluttonousSnake(QWidget *parent = nullptr);
    ~GluttonousSnake();
private:
    //初始化ui
    void initui();
    //信号连接
    void signConnect();
    //退出事件
    void closeEvent ( QCloseEvent *);



private:
    Ui::GluttonousSnake *ui;
    gameweight * gameStart;
    GluttonousSnake *parent;

//槽函数
private:
    //启动子窗口
    void start();



};
#endif // GLUTTONOUSSNAKE_H
