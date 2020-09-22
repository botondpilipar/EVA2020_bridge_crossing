#ifndef BRIDGECROSSINGBOARD_H
#define BRIDGECROSSINGBOARD_H

#include "IGameBoard.h"
#include "BridgeCrossingBoardData.h"
#include "BridgeCrossingPlayer.h"

namespace kd417d
{
namespace eva
{
namespace logic
{
using namespace bridge;

class BridgeCrossingBoard : public IGameBoard<BoardData>,
                            public QObject
{
    Q_OBJECT;
public:
    virtual void addPlayer(const BridgeCrossingPlayer& player);
    virtual bool removePlayer(int uniquePlayerId);

    // IGameBoard
    virtual Dimension2D getDimensions() override;
    virtual void setDimensions(Dimension2D&) override;

    // IGameControlUnit
    virtual void startNewGame() override;
    virtual void pauseGame() override;
    virtual void continueGame() override;

    // ISettingsChangedObserver
    virtual void settingsChanged() override;

signals:
    void scoredPointChangedSignal(ScoredPoint newScore);
    void gameOverSignal(ScoredPoint finalScore);
    void newPlayerAddedSignal(BridgeCrossingPlayer& newPlayer);

protected:
    QList<BridgeCrossingPlayer*> mPlayers;
    QList<ISettingsChangedObserver*> mSettingsChangedObservers;
    QMap<int, BridgeCrossingPlayer> mPlayerIdMap;
    ScoredPoint mTimeElapsed;
    QStateMachine mStateMachine;

protected slots:
    void onPlayerActionPerformed(PlayerActionSet action);
};

}
}
}
#endif // BRIDGECROSSINGBOARD_H
