#ifndef BRIDGECROSSINGPLAYER_H
#define BRIDGECROSSINGPLAYER_H

#include "IGameActor.hpp"
#include "BridgeCrossingPlayerData.h"
#include "BridgeCrossingTypes.h"

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

    Q_PROPERTY(BridgeCrossingTypes::PlayerState mState
               READ getPlayerState
               NOTIFY notifyStateChanged)
    Q_PROPERTY(int mUniqueId
               READ getUniqueId)
    Q_PROPERTY(BridgeCrossingTypes::PlayerType mType
               READ getPlayerType)
    Q_PROPERTY(CrossSpeed mCrossSpeed
               READ getCrossSpeed)
public:
    virtual ~BridgeCrossingPlayer() override = default;
    BridgeCrossingPlayer() = default;
    BridgeCrossingPlayer(int uniqueId) {}

    inline BridgeCrossingTypes::PlayerState getPlayerState() const { return mState; }

    inline BridgeCrossingTypes::PlayerType getPlayerType() const { return mType; }

    inline CrossSpeed getCrossSpeed() const { return mCrossSpeed; }

    // IGameActor
    virtual void performAction(BridgeCrossingTypes::PlayerActionSet action) override;
    virtual int getUniqueId() const override
    {
        return mUniqueId;
    }

    // IMovableObject
    virtual void move(QPair<int, int> newPosition) override;
    virtual QPair<int, int> getPositionOnBoard() const override;

    // IDataInitializable
    virtual void initialize(const PlayerData& representation) override;
    virtual PlayerData* save() const override;

    // ISettingsChangedObserver

    virtual void settingsChanged() override;
signals:
    void actionPerformedSignal(BridgeCrossingTypes::PlayerActionSet action);
    void notifyStateChanged(BridgeCrossingTypes::PlayerState state);

private:
    int mUniqueId;
    BridgeCrossingTypes::PlayerState mState;
    BridgeCrossingTypes::PlayerType mType;
    CrossSpeed mCrossSpeed;
};

}
}
}
#endif // BRIDGECROSSINGPLAYER_H
