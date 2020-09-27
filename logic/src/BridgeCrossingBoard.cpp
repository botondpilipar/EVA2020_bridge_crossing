#include <BridgeCrossingBoard.h>
#include <SingletonFactory.hpp>
#include <UnimplementedException.h>

using namespace kd417d::eva::logic;

BridgeCrossingBoard::BridgeCrossingBoard()
    : mGameState(BridgeCrossingTypes::GameState::CROSS_SELECTION),
      mSettings(SingletonFactory<BridgeCrossingSettings>::instance()),
      mRandomDevice(SingletonFactory<CachedRandomDevice>::instance())
{
    mBridgeBuffer.resize(BridgeCrossingSettingDefaults::playersCanCrossAtOneTime);

    for(unsigned i = 0; i<mSettings.getSlowPlayerNumber(); ++i)
    {
        Identifier id = mRandomDevice.random();
        BridgeCrossingPlayer* player = new BridgeCrossingPlayer(id,
                                                                BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                BridgeCrossingTypes::PlayerType::SLOW);
        mPlayerIdMap.insert(id, player);
        mPlayers.append(player);
    }
    for(unsigned i = 0; i<mSettings.getMediumPlayerNumber(); ++i)
    {
        Identifier id = mRandomDevice.random();
        BridgeCrossingPlayer* player = new BridgeCrossingPlayer(id,
                                                                BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                BridgeCrossingTypes::PlayerType::MEDIUM);
        mPlayerIdMap.insert(id, player);
        mPlayers.append(player);
    }
    for(unsigned i = 0; i<mSettings.getFastPlayerNumber(); ++i)
    {
        Identifier id = mRandomDevice.random();
        BridgeCrossingPlayer* player = new BridgeCrossingPlayer(id,
                                                                BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                BridgeCrossingTypes::PlayerType::FAST);
        mPlayerIdMap.insert(id, player);
        mPlayers.append(player);
    }

    connectToPlayers();
}

BridgeCrossingBoard::~BridgeCrossingBoard()
{
    for(BridgeCrossingPlayer* p : mPlayers)
    {
        delete p;
    }
}

void
BridgeCrossingBoard::cross()
{
    switch(mGameState)
    {
        case BridgeCrossingTypes::GameState::CROSS_SELECTION:
        {
            for(auto player : mBridgeBuffer)
            {
                player->performAction(BridgeCrossingTypes::PlayerActionSet::CROSS);
            }
            break;
        }
        case BridgeCrossingTypes::GameState::RETURN_SELECTION:
        {
            for(auto player : mBridgeBuffer)
            {
                player->performAction(BridgeCrossingTypes::PlayerActionSet::RETURN);
            }
            break;
        }
    }
    mBridgeBuffer.clear();
}

void
BridgeCrossingBoard::movePlayer(Identifier uniquePlayerId)
{
    if(!mPlayerIdMap.contains(uniquePlayerId))
    {
        return;
    }

    mPlayerIdMap.value(uniquePlayerId)->performAction(BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE);

}

Dimension2D
BridgeCrossingBoard::getDimensions() const
{
    throw new UnimplementedException("BridgeCrossingBoard", "getDimensions");
}

void
BridgeCrossingBoard::setDimensions(Dimension2D&)
{
    throw new UnimplementedException("BridgeCrossingBoard", "setDimensions");
}

BridgeCrossingTypes::GameState BridgeCrossingBoard::getGameState() const
{
    return mGameState;
}

ScoredPoint BridgeCrossingBoard::getTimeEllapsed() const
{
    return mTimeEllapsed;
}

void
BridgeCrossingBoard::startNewGame()
{
    mTimeEllapsed = 0;
    mBridgeBuffer.clear();
    mGameState = BridgeCrossingTypes::GameState::CROSS_SELECTION;
    mIsPaused = false;
    QMap<Identifier, std::shared_ptr<PlayerData>> playerIdData{};
    QList<PlayerData*> toFree;

    for(BridgeCrossingPlayer* player : mPlayers)
    {
        player->setPlayerState(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
        PlayerData* data = player->save();
        playerIdData.insert(player->getUniqueId(), std::shared_ptr<PlayerData>(data));
    }

    emit newGameSignal();
    emit boardChangedSignal(playerIdData);
}

void
BridgeCrossingBoard::pauseGame()
{
    if(mIsPaused)
    {
        return;
    }
    disconnectFromPlayers();
    mIsPaused = true;
}

void
BridgeCrossingBoard::continueGame()
{
    if(!mIsPaused)
    {
        return;
    }
    connectToPlayers();
    mIsPaused = false;
}

void
BridgeCrossingBoard::settingsChanged()
{
    startNewGame();
}

void
BridgeCrossingBoard::onPlayerActionPerformed(BridgeCrossingTypes::PlayerActionSet action)
{
    return;
}

void BridgeCrossingBoard::initialize(const BoardData& data)
{
    mTimeEllapsed = data.point;
    mGameState = data.state;

    mPlayerIdMap.clear();
    if(mPlayers.size() < data.playerData.size())
    {
        mPlayers.resize(data.playerData.size());
        for(int i = 0; i<data.playerData.size() - mPlayers.size(); ++i)
        {
            Identifier id = mRandomDevice.random();
            mPlayers.push_back(new BridgeCrossingPlayer(
                                   id,
                                   BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                   BridgeCrossingTypes::PlayerType::FAST));
        }
    }

    for(int i = 0; i<mPlayers.size(); ++i)
    {
        auto currentPlayer = mPlayers.at(i);
        currentPlayer->initialize(*data.playerData.at(i));
        mPlayerIdMap.insert(currentPlayer->getUniqueId(), currentPlayer);
    }
}

BoardData* BridgeCrossingBoard::save() const
{
    QVector<PlayerData> playerData(mPlayers.size());
}

void
BridgeCrossingBoard::connectToPlayers()
{
    for(BridgeCrossingPlayer* player : mPlayers)
    {
        QObject::connect(player, &BridgeCrossingPlayer::actionPerformedSignal,
                         this, &BridgeCrossingBoard::onPlayerActionPerformed);
    }
}

void BridgeCrossingBoard::disconnectFromPlayers()
{
    for(BridgeCrossingPlayer* player : mPlayers)
    {
        QObject::disconnect(player, &BridgeCrossingPlayer::actionPerformedSignal,
                         this, &BridgeCrossingBoard::onPlayerActionPerformed);
    }
}
