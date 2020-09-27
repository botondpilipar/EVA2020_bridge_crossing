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
        std::shared_ptr<BridgeCrossingPlayer> player = std::make_shared<BridgeCrossingPlayer>(id,
                                                                BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                BridgeCrossingTypes::PlayerType::SLOW);
        mPlayerIdMap.insert(id, player);
        mPlayers.append(player);
    }
    for(unsigned i = 0; i<mSettings.getMediumPlayerNumber(); ++i)
    {
        Identifier id = mRandomDevice.random();
        std::shared_ptr<BridgeCrossingPlayer> player = std::make_shared<BridgeCrossingPlayer>(id,
                                                                BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                BridgeCrossingTypes::PlayerType::MEDIUM);
        mPlayerIdMap.insert(id, player);
        mPlayers.append(player);
    }
    for(unsigned i = 0; i<mSettings.getFastPlayerNumber(); ++i)
    {
        Identifier id = mRandomDevice.random();
        std::shared_ptr<BridgeCrossingPlayer> player = std::make_shared<BridgeCrossingPlayer>(id,
                                                                BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                                BridgeCrossingTypes::PlayerType::FAST);
        mPlayerIdMap.insert(id, player);
        mPlayers.append(player);
    }

    connectToPlayers();
}

BridgeCrossingBoard::~BridgeCrossingBoard()
{
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
    throw UnimplementedException("BridgeCrossingBoard", "getDimensions");
}

void
BridgeCrossingBoard::setDimensions(Dimension2D&)
{
    throw UnimplementedException("BridgeCrossingBoard", "setDimensions");
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

    for(const auto& player : mPlayers)
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
    BridgeCrossingPlayer* sender = qobject_cast<BridgeCrossingPlayer*>(QObject::sender());
    if(mIsPaused)
    {
        return;
    }

    QMap<Identifier, std::shared_ptr<PlayerData>> changed{};

    switch(action)
    {
        case BridgeCrossingTypes::PlayerActionSet::CROSS:
        {
            mGameState = BridgeCrossingTypes::GameState::RETURN_SELECTION;
            changed.insert(sender->getUniqueId(), std::shared_ptr<PlayerData>(sender->save()));
            break;
        }
        case BridgeCrossingTypes::PlayerActionSet::RETURN:
        {
            mGameState = BridgeCrossingTypes::GameState::CROSS_SELECTION;
            changed.insert(sender->getUniqueId(), std::shared_ptr<PlayerData>(sender->save()));
            break;
        }
        case BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE:
        {
            switch(sender->getPlayerState())
            {
                case BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE:
                case BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE:
                {
                    auto iteratorToSender = std::find(mBridgeBuffer.begin(), mBridgeBuffer.end(), sender);
                    assert(iteratorToSender != mBridgeBuffer.end());

                    mBridgeBuffer.erase(iteratorToSender);
                    changed.insert(sender->getUniqueId(), std::shared_ptr<PlayerData>(sender->save()));
                    break;
                }
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS:
                {
                    mGameState = BridgeCrossingTypes::GameState::CROSS_SELECTION;
                    if(isBridgeBufferFull())
                    {
                        sender->setPlayerState(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
                    }
                    else
                    {
                        mBridgeBuffer.push_back(sender);
                        changed.insert(sender->getUniqueId(), std::shared_ptr<PlayerData>(sender->save()));
                    }
                    break;
                }
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN:
                {
                    mGameState = BridgeCrossingTypes::GameState::RETURN_SELECTION;

                    if(isBridgeBufferFull())
                    {
                        sender->setPlayerState(BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE);
                    }
                    else
                    {
                        mBridgeBuffer.push_back(sender);
                        changed.insert(sender->getUniqueId(), std::shared_ptr<PlayerData>(sender->save()));
                    }
                    break;
                }
            }
            break;
        }
    }

    emit boardChangedSignal(changed);
}

void BridgeCrossingBoard::initialize(const BoardData& data)
{
    mTimeEllapsed = data.point;
    mGameState = data.state;
    mPlayerIdMap.clear();
    PlayerIdMap changed;

    mPlayers.resize(data.playerData.size());
    for(const auto& playerDataPtr : data.playerData)
    {
        std::shared_ptr<BridgeCrossingPlayer> newPlayer
                = std::make_shared<BridgeCrossingPlayer>(0,
                                                        BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE,
                                                        BridgeCrossingTypes::PlayerType::FAST);
        newPlayer->initialize(*playerDataPtr);
        mPlayerIdMap.insert(newPlayer->getUniqueId(), newPlayer);
        changed.insert(newPlayer->getUniqueId(), playerDataPtr);
    }

    emit boardChangedSignal(changed);
}

BoardData* BridgeCrossingBoard::save() const
{
    QVector<std::shared_ptr<PlayerData>> playerData{};

    std::transform(mPlayers.begin(), mPlayers.end(), std::back_inserter(playerData),
                   [](const auto& player){ return std::shared_ptr<PlayerData>(player->save()); });

    return new BoardData(playerData,
                     mTimeEllapsed,
                     mPlayers.size(),
                     mGameState);
}

void
BridgeCrossingBoard::connectToPlayers()
{
    for(const auto& player : mPlayers)
    {
        QObject::connect(player.get(), &BridgeCrossingPlayer::actionPerformedSignal,
                         this, &BridgeCrossingBoard::onPlayerActionPerformed);
    }
}

void BridgeCrossingBoard::disconnectFromPlayers()
{
    for(const auto& player : mPlayers)
    {
        QObject::disconnect(player.get(), &BridgeCrossingPlayer::actionPerformedSignal,
                         this, &BridgeCrossingBoard::onPlayerActionPerformed);
    }
}
