#ifndef BRIDGECROSSINGPLAYERDATA_H
#define BRIDGECROSSINGPLAYERDATA_H

#include <ISerializable.h>
#include <IDeserializable.h>
#include <DeserializationFailedException.h>

#include "GameLogicTypes.h"

namespace kd417d
{
namespace eva
{
namespace logic
{
namespace bridge
{

using namespace kd417d::eva::access;

struct PlayerData : public ISerializable, public IDeserializable
{
    virtual ~PlayerData() override = default;

    PlayerData();

    PlayerData(PlayerState state, Identifier id, PlayerType type, CrossSpeed speed)
        : state(state), id(id), type(type), speed(speed) {}

    PlayerState state;
    Identifier id;
    PlayerType type;
    CrossSpeed speed;

    virtual void deserialize(ISerializationSource&) override;

    virtual void serialize(ISerializationTarget&) override;
};

}


}
}
}
#endif // BRIDGECROSSINGPLAYERDATA_H
