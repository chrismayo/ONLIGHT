#include "selectcolor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectColor w;
    w.show();

    return a.exec();
}
