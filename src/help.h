#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include "const_string.h"
namespace Ui {
class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = nullptr);
    ~help();
private:
    void intitui();
private:
    Ui::help *ui;
};

#endif // HELP_H
