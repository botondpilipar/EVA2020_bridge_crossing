#include "bridgecrossingviewmanager.h"
#include "ui_bridgecrossingviewmanager.h"

BridgeCrossingViewManager::BridgeCrossingViewManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BridgeCrossingViewManager)
{
    ui->setupUi(this);
}

BridgeCrossingViewManager::~BridgeCrossingViewManager()
{
    delete ui;
}

