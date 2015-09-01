#include "englishinput.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnglishInput w;
    w.show();

    return a.exec();
}
