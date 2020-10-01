#ifndef BRIDGECROSSINGVIEWMANAGER_H
#define BRIDGECROSSINGVIEWMANAGER_H

#include <QMainWindow>
#include <BridgeCrossingBoard.h>
#include <QPushButton>
#include "SettingsDialog.h"
#include <common_pch.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BridgeCrossingViewManager; }
QT_END_NAMESPACE

class BridgeCrossingViewManager : public QMainWindow
{
    Q_OBJECT

public:
    BridgeCrossingViewManager(QWidget *parent = nullptr);
    ~BridgeCrossingViewManager();

protected slots:
    void onGameBoardChanged(PlayerIdMap change);
    void onNewGameStarted();
    void onPlayerStep();
    void onCrossButtonPushed();
    void onScoredPointChanged(ScoredPoint);
    void onGameOver(ScoredPoint finalScore);

    void onPlayingStateEntered();
    void onPausedStateEntered();
    void onSettingsStateEntered();

private:
    Ui::BridgeCrossingViewManager *ui;
    SettingsDialog mSettingsDialog;
    BridgeCrossingBoard mBoard;

    QVector<std::shared_ptr<QPushButton>> mPlayers;
    QMap<Identifier, std::shared_ptr<QPushButton>> mIdentifiedPlayers;
    QMap<std::shared_ptr<QPushButton>, QLayout*> mPlayerPositions;
    bool mIsInitialState;
    PlayerIdMap mLastGameState;
    QStateMachine mGameState;

    void initialBoardSetup(PlayerIdMap& change);
};
#endif // BRIDGECROSSINGVIEWMANAGER_H
