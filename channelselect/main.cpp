#include "channelselect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChannelSelect w;
    w.show();

    return a.exec();
}
