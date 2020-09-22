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
                             public IGameActor<PlayerData, BridgeCrossingTypes::PlayerActionSet>
{
    Q_OBJECT;

    Q_PROPERTY(PlayerState mState
               READ getPlayerState)
    Q_PROPERTY(int mUniqueId
               READ getUniqueId)
public:
    virtual ~BridgeCrossingPlayer() override = default;
    BridgeCrossingPlayer() = default;
    BridgeCrossingPlayer(int uniqueId) {}
    BridgeCrossingTypes::PlayerState getPlayerState()
    {
        return BridgeCrossingTypes::PlayerState::CROSSING;
    }

    // IGameActor
    virtual void performAction(BridgeCrossingTypes::PlayerActionSet action) override;
    virtual int getUniqueId() override
    {
        return mUniqueId;
    }

    // IMovableObject
    virtual void move(QPair<int, int> newPosition) override;
    virtual QPair<int, int> getPositionOnBoard() override;

    // IDataInitializable
    virtual void initialize(const PlayerData& representation) override;
    virtual PlayerData* save() override;

    // ISettingsChangedObserver

    virtual void settingsChanged() override;
signals:
    void actionPerformedSignal(BridgeCrossingTypes::PlayerActionSet action);

private:
    int mUniqueId;
};

}
}
}
#endif // BRIDGECROSSINGPLAYER_H
