#include <SingletonFactory.hpp>
#include <BridgeCrossingSettings.h>
#include <CachedRandomDevice.h>
#include "BridgeCrossingViewManager.h"

#include <QApplication>

using namespace kd417d::eva;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SingletonFactory<BridgeCrossingSettings>::setFactory(new BridgeCrossingSettings());
    SingletonFactory<CachedRandomDevice>::setFactory(new CachedRandomDevice());

    BridgeCrossingViewManager w;
    w.show();
    return a.exec();
}
