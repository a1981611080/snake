#ifndef SEED_H
#define SEED_H

#include <QObject>
#include "zuobiao.h"
#include "util.h"
class seed : public QObject
{
    Q_OBJECT
public:
    explicit seed(QObject *parent = nullptr);
    void setMap(int(*map)[55]);
    void add(zuobiao *);
    void del(int x,int y);
    void shengcheng();
    zuobiao* getseed();

signals:
private:
    int(*map)[55];
    zuobiao *seedHead=NULL;
    bool isEmply();




};

#endif // SEED_H
