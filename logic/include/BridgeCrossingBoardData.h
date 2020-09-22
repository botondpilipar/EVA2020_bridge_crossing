#ifndef BRIDGECROSSINGBOARDDATA_H
#define BRIDGECROSSINGBOARDDATA_H

#include <common_pch.h>
#include <ISerializable.h>
#include <IDeserializable.h>
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

struct PlayerData;

struct BoardData : public ISerializable,
                   public IDeserializable
{
    virtual ~BoardData() override = default;

    BoardData();
    BoardData(QVector<PlayerData>& playerData,
              ScoredPoint point,
              unsigned int playerNumber,
              GameState state);
    BoardData(const BoardData& other);
    BoardData(BoardData&& other);

    BoardData& operator=(const BoardData& other);

    BoardData& operator=(const BoardData&& other);

    virtual void deserialize(ISerializationSource&) override;

    virtual void serialize(ISerializationTarget&) override;

    ScoredPoint point;
    GameState state;
    unsigned int playerNumber;
    QVector<PlayerData> playerData;

};

}

}
}
}

#endif // BRIDGECROSSINGBOARDDATA_H
