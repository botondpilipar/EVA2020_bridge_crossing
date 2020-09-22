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

class BridgeCrossingPlayer : public IGameActor<PlayerData, PlayerActionSet>
{
public:
    virtual ~BridgeCrossingPlayer() override = default;
    BridgeCrossingPlayer();

    // IGameActor
    virtual void performAction(PlayerActionSet action) override;
    virtual int getUniqueId() override;

    // IMovableObject
    virtual void move(QPair<int, int> newPosition) override;
    virtual QPair<int, int> getPositionOnBoard() override;

    // IDataInitializable
    virtual void initialize(const PlayerData& representation) override;
    virtual PlayerData* save() override;


};

}
}
}
#endif // BRIDGECROSSINGPLAYER_H
