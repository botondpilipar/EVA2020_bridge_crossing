#include <BridgeCrossingPlayer.h>
#include <UnimplementedException.h>
#include <SingletonFactory.hpp>
#include <CachedRandomDevice.h>

using namespace kd417d::eva::logic;

BridgeCrossingPlayer::BridgeCrossingPlayer(Identifier uniqueId,
                                           BridgeCrossingTypes::PlayerState state,
                                           BridgeCrossingTypes::PlayerType type)
    : mUniqueId(uniqueId),
      mState(state),
      mType(type),
      mSettings(SingletonFactory<BridgeCrossingSettings>::instance())
{
    switch(mType)
    {
        case BridgeCrossingTypes::PlayerType::SLOW:
        {
            mCrossSpeed = mSettings.getSlowPlayerCrossTime();
            break;
        }
        case BridgeCrossingTypes::PlayerType::MEDIUM:
        {
            mCrossSpeed = mSettings.getMediumPlayerCrossTime();
            break;
        }
        case BridgeCrossingTypes::PlayerType::FAST:
        {
            mCrossSpeed = mSettings.getFastPlayerCrossTime();
            break;
        }
    }
}


// IGameActor
 void
 BridgeCrossingPlayer::performAction(BridgeCrossingTypes::PlayerActionSet action)
 {
     switch(action)
     {
        case BridgeCrossingTypes::PlayerActionSet::CROSS:
        {
         switch(mState)
         {
            case BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS:
             {
                setPlayerState(BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE);
                emit actionPerformedSignal(action);
                break;
             }
             default:
                 break;
         }
        }
            break;
        case BridgeCrossingTypes::PlayerActionSet::MOVE_TO_BRIDGE:
         {
            switch(mState)
            {
                case BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE:
                {
                    setPlayerState(BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS);
                    emit actionPerformedSignal(action);
                    break;
                }
                case BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE:
                {
                    setPlayerState(BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN);
                    emit actionPerformedSignal(action);
                    break;
                }
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_CROSS:
                {
                    setPlayerState(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
                    emit actionPerformedSignal(action);
                    break;
                }
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN:
                {
                    setPlayerState(BridgeCrossingTypes::PlayerState::ON_RETURNING_SIDE);
                    emit actionPerformedSignal(action);
                    break;
                }
                default:
                    break;
            }
         }
            break;
        case BridgeCrossingTypes::PlayerActionSet::RETURN:
         {
            switch(mState)
            {
                case BridgeCrossingTypes::PlayerState::SELECTED_TO_RETURN:
                {
                    setPlayerState(BridgeCrossingTypes::PlayerState::ON_CROSSING_SIDE);
                    emit actionPerformedSignal(action);
                    break;
                }
                default:
                    break;
            }
            break;
         }
     }
 }

// IMovableObject
 void
 BridgeCrossingPlayer::move(QPair<int, int>)
 {
    throw UnimplementedException("BridgeCrossingPlayer", "move");
 }

 QPair<int, int> BridgeCrossingPlayer::getPositionOnBoard() const
 {
     throw UnimplementedException("BridgeCrossingPlayer", "getPositionOnBoard");
 }

// IDataInitializable
 void
 BridgeCrossingPlayer::initialize(const PlayerData& representation)
 {
     mUniqueId  = representation.id;
     mType = representation.type;
     mCrossSpeed = representation.speed;
     mState = representation.state;
 }

 PlayerData*
 BridgeCrossingPlayer::save() const
 {
     return new PlayerData(mState,
                           mUniqueId,
                           mType,
                           mCrossSpeed);
 }

// ISettingsChangedObserver

void BridgeCrossingPlayer::settingsChanged()
{
    switch(mType)
    {
        case BridgeCrossingTypes::PlayerType::SLOW:
        {
            mCrossSpeed = mSettings.getSlowPlayerCrossTime();
        }
        case BridgeCrossingTypes::PlayerType::MEDIUM:
        {
            mCrossSpeed = mSettings.getMediumPlayerCrossTime();
        }
        case BridgeCrossingTypes::PlayerType::FAST:
        {
            mCrossSpeed = mSettings.getFastPlayerCrossTime();
        }
    }
}
