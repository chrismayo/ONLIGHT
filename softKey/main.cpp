#include <QtGui/QApplication>
#include "softkeypad.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoftKeyPad w;
    w.show();
    
    return a.exec();
}
