#include "upqp.h"
upQp::upQp(QString a,QString b,QWidget *parent):QPushButton(parent)
{
    la[0]=a;
    la[1]=b;
    setText(la[0]);
//    connect(this,&QPushButton::released,[this](){this->trychange();});
    merry=NULL;
}
bool upQp::getZhuantai(){
    return zhuantai;
}
void upQp::change(){
    zhuantai=!zhuantai;
    if(zhuantai) setText(la[1]);
    else{
        setText(la[0]);
        emit recovery();
    }
}

void upQp::trychange()
{
   bool chan=true;
   if(merry!=NULL){
       chan=merry->getZhuantai();
   }
   if(chan)
   {
       change();
   }

}
void upQp::setMerry(upQp *temp)
{
    merry=temp;
    connect(merry,&upQp::recovery,this,&upQp::rec);
}
void upQp::rec()
{
    zhuantai=false;
    setText(la[0]);
}
