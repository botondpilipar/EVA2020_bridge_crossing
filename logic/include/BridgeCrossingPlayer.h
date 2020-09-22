#ifndef BRIDGECROSSINGPLAYER_H
#define BRIDGECROSSINGPLAYER_H

#include "IGameActor.hpp"
#include "BridgeCrossingPlayerData.h"
#include "GameLogicTypes.h"

namespace kd417d
{
namespace eva
{
namespace logic
{
using namespace bridge;

class BridgeCrossingPlayer : public QObject,
                             public IGameActor<PlayerData, PlayerActionSet>
{
    Q_OBJECT;

    Q_PROPERTY(PlayerState mState
               READ getPlayerState)
public:
    virtual ~BridgeCrossingPlayer() override = default;
    BridgeCrossingPlayer();
    inline PlayerState getPlayerState();

    // IGameActor
    virtual void performAction(PlayerActionSet action) override;
    virtual int getUniqueId() override;

    // IMovableObject
    virtual void move(QPair<int, int> newPosition) override;
    virtual QPair<int, int> getPositionOnBoard() override;

    // IDataInitializable
    virtual void initialize(const PlayerData& representation) override;
    virtual PlayerData* save() override;

    // ISettingsChangedObserver

    virtual void settingsChanged() override;
signals:
    void actionPerformedSignal(PlayerActionSet action);
};

}
}
}
#endif // BRIDGECROSSINGPLAYER_H
