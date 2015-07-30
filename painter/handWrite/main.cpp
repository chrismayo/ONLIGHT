#include "handwrite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HandWrite w;
    w.show();

    return a.exec();
}
