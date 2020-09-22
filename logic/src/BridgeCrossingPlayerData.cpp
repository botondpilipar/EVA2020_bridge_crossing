#include <BridgeCrossingPlayerData.h>
#include <ISerializationTarget.h>
#include <ISerializationSource.h>
#include <GameLogicTypes.h>
#include <DeserializationFailedException.h>
#include <CachedRandomDevice.h>
#include <SingletonFactory.hpp>

using namespace kd417d::eva;
using namespace kd417d::eva::logic::bridge;

PlayerData::PlayerData()
    : state(PlayerState::CROSSING),
      id(SingletonFactory<CachedRandomDevice>::instance().random()),
      type(PlayerType::SLOW),
      speed(0)
{}

void
PlayerData::serialize(ISerializationTarget& target)
{
    target.serializeInt(id);
    target.serializeInt(static_cast<std::underlying_type_t<PlayerState>>(state));
    target.serializeInt(static_cast<std::underlying_type_t<PlayerState>>(type));
    target.serializeUnsigned(speed);
}

void
PlayerData::deserialize(ISerializationSource& source)
{
    std::tuple deserialized = { source.deserializeInt(),
                                source.deserializeInt(),
                                source.deserializeInt(),
                                source.deserializeUnsigned() };
    auto [id, state, type, speed] = deserialized;
    if(id.has_value() && state.has_value() && type.has_value() && speed.has_value())
    {
        this->id = id.value();
        this->state = static_cast<PlayerState>(state.value());
        this->type = static_cast<PlayerType>(type.value());
        this->speed = speed.value();
    }
    else
    {
        throw DeserializationFailedException("PlayerData");
    }
}
