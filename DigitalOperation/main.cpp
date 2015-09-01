#include "digitaloperation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DigitalOperation w;
    w.show(1.3E+4, 4E+5 , 2, false);

    return a.exec();
}
