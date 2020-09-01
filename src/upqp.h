#ifndef UPQP_H
#define UPQP_H

#include <QPushButton>
#include <QWidget>
class upQp : public QPushButton
{
    Q_OBJECT

public:

    explicit upQp(QString,QString,QWidget *parent=nullptr);
private:
    bool zhuantai=false;
    QString la[2];
    void change();
    upQp *merry;
public:
    bool getZhuantai();
    void setMerry(upQp*);
    void trychange();
private slots:

    void rec();
signals:
    void recovery();


};

#endif // UPQP_H
