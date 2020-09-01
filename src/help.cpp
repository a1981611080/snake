#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    intitui();
}

help::~help()
{
    delete ui;
}
void help::intitui(){
    this->setWindowTitle(_L9);
    ui->label->setText(_L9);
    ui->label_2->setText(_L14);
    ui->label_3->setText(_L15);
    ui->label_4->setText(_L18);
    ui->label_5->setText(_L17);
    ui->label_6->setText(_L19);
    ui->label_7->setText(_L16);
}
