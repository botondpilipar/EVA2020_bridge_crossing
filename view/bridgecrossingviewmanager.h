#ifndef BRIDGECROSSINGVIEWMANAGER_H
#define BRIDGECROSSINGVIEWMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BridgeCrossingViewManager; }
QT_END_NAMESPACE

class BridgeCrossingViewManager : public QMainWindow
{
    Q_OBJECT

public:
    BridgeCrossingViewManager(QWidget *parent = nullptr);
    ~BridgeCrossingViewManager();

private:
    Ui::BridgeCrossingViewManager *ui;
};
#endif // BRIDGECROSSINGVIEWMANAGER_H
