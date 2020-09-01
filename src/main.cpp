#include "gluttonoussnake.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GluttonousSnake w;
    w.show();

    return a.exec();
}
