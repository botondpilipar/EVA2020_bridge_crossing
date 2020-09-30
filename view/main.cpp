#include "bridgecrossingviewmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BridgeCrossingViewManager w;
    w.show();
    return a.exec();
}
