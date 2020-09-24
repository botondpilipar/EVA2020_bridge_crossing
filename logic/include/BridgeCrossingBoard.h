#ifndef BRIDGECROSSINGBOARD_H
#define BRIDGECROSSINGBOARD_H

#include "IGameBoard.h"
#include "BridgeCrossingBoardData.h"
#include "BridgeCrossingPlayer.h"
#include "BridgeCrossingTypes.h"

namespace kd417d
{
namespace eva
{
namespace logic
{
using namespace bridge;

class BridgeCrossingBoard : public QObject,
                            public IGameBoard<BoardData>
{
    Q_OBJECT

    Q_PROPERTY(BridgeCrossingTypes::GameState mGameState
               READ getGameState);
    Q_PROPERTY(ScoredPoint mTimeEllapsed
               READ getTimeEllapsed)
public:
    virtual void addPlayer(const BridgeCrossingPlayer& player);
    virtual void movePlayer(int uniquePlayerId);
    virtual BridgeCrossingTypes::GameState getGameState();
    virtual void cross();
    virtual BridgeCrossingTypes::GameState getGameState() const;
    virtual ScoredPoint getTimeEllapsed() const;

    // IGameBoard
    virtual Dimension2D getDimensions() const override;
    virtual void setDimensions(Dimension2D&) override;

    // IGameControlUnit
    virtual void startNewGame() override;
    virtual void pauseGame() override;
    virtual void continueGame() override;

    // ISettingsChangedObserver
    virtual void settingsChanged() override;

signals:
    void scoredPointChangedSignal(ScoredPoint newScore);
    void newPlayerAddedSignal(BridgeCrossingPlayer& newPlayer);
    void playerMovedSignal(const BridgeCrossingPlayer&);
    void gameOverSignal(ScoredPoint finalScore);
    void newGameSignal();
    void boardChangedSignal(const QMap<int, BridgeCrossingPlayer>&);

protected:
    QList<BridgeCrossingPlayer*> mPlayers;
    QList<ISettingsChangedObserver*> mSettingsChangedObservers;
    QMap<int, BridgeCrossingPlayer> mPlayerIdMap;
    ScoredPoint mTimeEllapsed;
    QStateMachine mStateMachine;

protected slots:
    void onPlayerActionPerformed(BridgeCrossingTypes::PlayerActionSet action);
};

}
}
}
#endif // BRIDGECROSSINGBOARD_H
